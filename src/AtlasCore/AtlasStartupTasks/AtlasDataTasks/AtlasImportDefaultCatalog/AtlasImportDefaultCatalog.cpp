#include "AtlasCore/AtlasMath/AtlasProjectionMath/AtlasProjectionMath.h"
#include "AtlasCore/AtlasStarObjects/AtlasStar.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDataTasks/AtlasImportDefaultCatalog/AtlasImportDefaultCatalog.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDefaultCatalogRecord/AtlasFetchDefaultCatalogRecord.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <algorithm>
#include <expected>
#include <fitsio.h>
#include <format>
#include <longnam.h>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::expected<bool, std::string> AtlasImportDefaultCatalog::load()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> importDefaultCatalogResult = true;

	importDefaultCatalogResult = importDefaultCatalogResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasDatabaseUtilities::open(&database); })
		.and_then([&](bool success) -> std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> { return AtlasFetchDefaultCatalogRecord::fetch(database); })
		.and_then([&](AtlasCatalogUtilities::CatalogRecord catalog) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::loadCatalog(catalog); });

	return importDefaultCatalogResult;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::loadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog)
{
	fitsfile* filePointer = nullptr;
	long totalCatalogRows = 0;

	std::expected<bool, std::string> loadCatalogResult = true;

	loadCatalogResult = loadCatalogResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsOpenFile(filePointer, catalog.path, &totalCatalogRows); });

	if (!loadCatalogResult.has_value()) {
		return loadCatalogResult;
	}

	int raIndex = 0;
	int deIndex = 0;
	int raProperMotionIndex = 0, decProperMotionIndex = 0;
	int vMagIndex = 0, bvIndex = 0;

	loadCatalogResult = loadCatalogResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsGetColumnIndex(filePointer, "RAJ2000", &raIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsGetColumnIndex(filePointer, "DEJ2000", &deIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsGetColumnIndex(filePointer, "pmRA", &raProperMotionIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsGetColumnIndex(filePointer, "pmDE", &decProperMotionIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsGetColumnIndex(filePointer, "Vmag", &vMagIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsGetColumnIndex(filePointer, "B-V", &bvIndex); });

	if (!loadCatalogResult.has_value()) {
		return loadCatalogResult;
	}

	std::vector<std::string> raBuffer(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);
	std::vector<std::string> deBuffer(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);
	std::vector<double> raProperMotionBuffer(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);
	std::vector<double> decProperMotionBuffer(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);
	std::vector<float> vMagBuffer(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);
	std::vector<float> bvBuffer(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);

	std::vector<AtlasStar> starObjectBuffer;
	starObjectBuffer.reserve(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE);

	long importBatchIndex = 1;
	while (importBatchIndex <= totalCatalogRows) {
		long importBatchSize = std::min(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE, totalCatalogRows - importBatchIndex + 1);

		loadCatalogResult = loadCatalogResult
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(filePointer, raIndex, importBatchIndex, importBatchSize, raBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(filePointer, deIndex, importBatchIndex, importBatchSize, deBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(filePointer, raProperMotionIndex, importBatchIndex, importBatchSize, raProperMotionBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(filePointer, decProperMotionIndex, importBatchIndex, importBatchSize, decProperMotionBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(filePointer, vMagIndex, importBatchIndex, importBatchSize, vMagBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(filePointer, bvIndex, importBatchIndex, importBatchSize, bvBuffer); });

		starObjectBuffer.clear();
		for (long i = 0; i < importBatchSize; ++i) {
			AtlasStar star;

			double raHours = 0.0, raMinutes = 0.0, raSeconds = 0.0;
			double deDegrees = 0.0, deMinutes = 0.0, deSeconds = 0.0;

			AtlasImportDefaultCatalog::getSexagesimalUnitsRA(raBuffer[i], raHours, raMinutes, raSeconds);
			AtlasImportDefaultCatalog::getSexagesimalUnitsDE(deBuffer[i], deDegrees, deMinutes, deSeconds);

			star.ra = AtlasProjectionMath::getRaRadians(raHours, raMinutes, raSeconds);
			star.de = AtlasProjectionMath::getDecRadians(deDegrees, deMinutes, deSeconds);
			star.pmRa = raProperMotionBuffer[i];
			star.pmDe = decProperMotionBuffer[i];
			star.mag = vMagBuffer[i];
			star.color = bvBuffer[i];
			star.bounds.minX = star.bounds.maxX = AtlasProjectionMath::getCartesianX(star.ra, star.de);
			star.bounds.minY = star.bounds.maxY = AtlasProjectionMath::getCartesianY(star.ra, star.de);
			star.bounds.minZ = star.bounds.maxZ = AtlasProjectionMath::getCartesianZ(star.de);

			starObjectBuffer.push_back(star);

			importBatchIndex += importBatchSize;
		}

		/* @todo insert records */
	}

	std::ignore = AtlasImportDefaultCatalog::fitsCloseFile(filePointer, catalog.path);

	return loadCatalogResult;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::fitsOpenFile(fitsfile* filePointer, std::string filePath, long* totalRows)
{
	int resultCode = 0;

	fits_open_file(&filePointer, filePath.c_str(), READONLY, &resultCode);

	fits_movabs_hdu(filePointer, 2, NULL, &resultCode);

	fits_get_num_rows(filePointer, totalRows, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error opening file {}: {} (Code: {})", filePath, fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::fitsCloseFile(fitsfile* filePointer, std::string filePath)
{
	int resultCode = 0;

	fits_close_file(filePointer, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error closing file {}: {} (Code: {})", filePath, fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::fitsGetColumnIndex(fitsfile* filePointer, std::string columnHeader, int* columnIndex)
{
	int resultCode = 0;

	char* columnHeaderPointer = &columnHeader[0];

	fits_get_colnum(filePointer, CASEINSEN, columnHeaderPointer, columnIndex, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error identifying column index: {} (Code: {})", fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(fitsfile* filePointer, int columnIndex, int importBatchSize, long importBatchIndex, std::vector<double>& dataBuffer)
{
	int resultCode;
	double defaultDoubleValue = 0.0;

	fits_read_col(filePointer, TDOUBLE, columnIndex, importBatchIndex, 1, importBatchSize, &defaultDoubleValue, dataBuffer.data(), nullptr, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error loading column into buffer: {} (Code: {})", fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(fitsfile* filePointer, int columnIndex, int importBatchSize, long importBatchIndex, std::vector<float>& dataBuffer)
{
	int resultCode;
	float defaultFloatValue = 0.0f;

	fits_read_col(filePointer, TFLOAT, columnIndex, importBatchIndex, 1, importBatchSize, &defaultFloatValue, dataBuffer.data(), nullptr, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error loading column into buffer: {} (Code: {})", fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	return true;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::fitsLoadColumnIntoBuffer(fitsfile* filePointer, int columnIndex, int importBatchSize, long importBatchIndex, std::vector<std::string>& dataBuffer)
{
	int resultCode;

	int displayWidth = 0;

	fits_get_col_display_width(filePointer, columnIndex, &displayWidth, &resultCode);

	std::vector<char> rawDataBlock(importBatchSize * (displayWidth + 1));

	std::vector<char*> pointersBuffer(importBatchSize);

	for (int i = 0; i < importBatchSize; i++) {
		int pointerIndex = i * (displayWidth + 1);
		pointersBuffer[i] = &rawDataBlock[pointerIndex];
	}

	fits_read_col_str(filePointer, columnIndex, importBatchIndex, 1, importBatchSize, (char*)"", pointersBuffer.data(), nullptr, &resultCode);

	if (resultCode) {
		char fitsErrorMessage[FLEN_ERRMSG];

		fits_read_errmsg(fitsErrorMessage);

		std::string error = std::format("Error loading column into buffer: {} (Code: {})", fitsErrorMessage, resultCode);

		return std::unexpected<std::string>(error);
	}

	dataBuffer.reserve(importBatchSize);

	for (int i = 0; i < importBatchSize; i++) {
		dataBuffer.push_back(std::string(pointersBuffer[i]));
	}

	return true;
}

bool AtlasImportDefaultCatalog::getSexagesimalUnitsRA(std::string ra, double& raHours, double& raMinutes, double& raSeconds)
{
	std::replace(ra.begin(), ra.end(), ':', ' ');

	std::stringstream stream(ra);

	if (stream >> raHours >> raMinutes >> raSeconds) {
		return true;
	}

	return false;
}

bool AtlasImportDefaultCatalog::getSexagesimalUnitsDE(std::string de, double& deDegrees, double& deMinutes, double& deSeconds)
{
	int sign = de.find('-') != std::string::npos ? -1 : 1;

	std::replace(de.begin(), de.end(), ':', ' ');
	std::replace(de.begin(), de.end(), '+', ' ');
	std::replace(de.begin(), de.end(), '-', ' ');

	std::stringstream stream(de);

	if (stream >> deDegrees >> deMinutes >> deSeconds) {
		return true;
	}

	return false;
}