#include "AtlasCore/AtlasMath/AtlasProjectionMath/AtlasProjectionMath.h"
#include "AtlasCore/AtlasStarObjects/AtlasStar.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDataTasks/AtlasImportDefaultCatalog/AtlasImportDefaultCatalog.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDefaultCatalogRecord/AtlasFetchDefaultCatalogRecord.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include "AtlasUtilities/AtlasFitsDataUtilities/AtlasFitsDataUtilities.h"
#include <algorithm>
#include <expected>
#include <fitsio.h>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <vector>

std::expected<bool, std::string> AtlasImportDefaultCatalog::load()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		return std::unexpected<std::string>(openDatabaseResult.error());
	}

	sqlite3* database = openDatabaseResult.value().get();

	std::expected<bool, std::string> importDefaultCatalogResult = true;

	importDefaultCatalogResult = importDefaultCatalogResult
		.and_then([&](bool success) -> std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> { return AtlasFetchDefaultCatalogRecord::fetch(database); })
		.and_then([&](AtlasCatalogUtilities::CatalogRecord catalog) -> std::expected<bool, std::string> { return AtlasImportDefaultCatalog::loadCatalog(catalog); });

	return importDefaultCatalogResult;
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::loadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog)
{
	long totalCatalogRows = 0;

	std::expected<bool, std::string> loadCatalogResult = true;

	std::expected<AtlasFitsDataUtilities::MemorySafeFitsFile, std::string> fitsFileResult = AtlasFitsDataUtilities::open(catalog.path);

	if (!fitsFileResult.has_value()) {
		return std::unexpected<std::string>(fitsFileResult.error());
	}

	fitsfile* file = fitsFileResult.value().get();

	int raIndex = 0;
	int deIndex = 0;
	int raProperMotionIndex = 0, decProperMotionIndex = 0;
	int vMagIndex = 0, bvIndex = 0;

	loadCatalogResult = loadCatalogResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::getColumnIndex(file, "RAJ2000", raIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::getColumnIndex(file, "DEJ2000", deIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::getColumnIndex(file, "pmRA", raProperMotionIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::getColumnIndex(file, "pmDE", decProperMotionIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::getColumnIndex(file, "Vmag", vMagIndex); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::getColumnIndex(file, "B-V", bvIndex); });

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
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::loadColumnIntoBuffer(file, raIndex, importBatchIndex, raBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::loadColumnIntoBuffer(file, deIndex, importBatchIndex, deBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::loadColumnIntoBuffer<double>(file, raProperMotionIndex, importBatchIndex, raProperMotionBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::loadColumnIntoBuffer<double>(file, decProperMotionIndex, importBatchIndex, decProperMotionBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::loadColumnIntoBuffer<float>(file, vMagIndex, importBatchIndex, vMagBuffer); })
			.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasFitsDataUtilities::loadColumnIntoBuffer<float>(file, bvIndex, importBatchIndex, bvBuffer); });

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

	return loadCatalogResult;
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