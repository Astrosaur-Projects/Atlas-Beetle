#include "AtlasCore/AtlasMath/AtlasProjectionMath/AtlasProjectionMath.h"
#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDataTasks/AtlasImportDefaultCatalog/AtlasImportDefaultCatalog.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDefaultCatalogRecord/AtlasFetchDefaultCatalogRecord.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasInsertBatchStarRenderData/AtlasInsertBatchStarRenderData.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include "AtlasUtilities/AtlasFitsDataUtilities/AtlasFitsDataUtilities.h"
#include <algorithm>
#include <cfitsio/fitsio.h>
#include <expected>
#include <numbers>
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

	return AtlasFetchDefaultCatalogRecord::fetch(database)
		.and_then([&](AtlasCatalogUtilities::CatalogRecord catalog) { return AtlasImportDefaultCatalog::loadCatalog(catalog, database); });
}

std::expected<bool, std::string> AtlasImportDefaultCatalog::loadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog, sqlite3* database)
{
	std::expected<AtlasFitsDataUtilities::MemorySafeFitsFile, std::string> openFitsFileResult = AtlasFitsDataUtilities::open(catalog.path);

	if (!openFitsFileResult.has_value()) {
		return std::unexpected<std::string>(openFitsFileResult.error());
	}

	fitsfile* file = openFitsFileResult.value().get();

	long totalCatalogRows = 0;

	std::expected<bool, std::string> loadCatalogResult = true;

	loadCatalogResult = loadCatalogResult
		.and_then([&](bool) { return AtlasFitsDataUtilities::moveToHeaderDataUnit(file, 2); })
		.and_then([&](bool) { return AtlasFitsDataUtilities::getRowCount(file, totalCatalogRows); });

	if (!loadCatalogResult.has_value()) {
		return std::unexpected<std::string>(loadCatalogResult.error());
	}

	int raIndex = 0;
	int deIndex = 0;
	int raProperMotionIndex = 0, decProperMotionIndex = 0;
	int vMagIndex = 0, bvIndex = 0;

	loadCatalogResult = loadCatalogResult
		.and_then([&](bool) { return AtlasFitsDataUtilities::getColumnIndex(file, "RAJ2000", raIndex); })
		.and_then([&](bool) { return AtlasFitsDataUtilities::getColumnIndex(file, "DEJ2000", deIndex); })
		.and_then([&](bool) { return AtlasFitsDataUtilities::getColumnIndex(file, "pmRA", raProperMotionIndex); })
		.and_then([&](bool) { return AtlasFitsDataUtilities::getColumnIndex(file, "pmDE", decProperMotionIndex); })
		.and_then([&](bool) { return AtlasFitsDataUtilities::getColumnIndex(file, "Vmag", vMagIndex); })
		.and_then([&](bool) { return AtlasFitsDataUtilities::getColumnIndex(file, "B-V", bvIndex); });

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

	while (loadCatalogResult.has_value() && (importBatchIndex <= totalCatalogRows)) {
		long importBatchSize = std::min(AtlasImportDefaultCatalog::STAR_IMPORT_BATCH_SIZE, totalCatalogRows - importBatchIndex + 1);

		loadCatalogResult = loadCatalogResult
			.and_then([&](bool) { return AtlasFitsDataUtilities::loadColumnIntoBuffer(file, raIndex, importBatchIndex, importBatchSize, raBuffer); })
			.and_then([&](bool) { return AtlasFitsDataUtilities::loadColumnIntoBuffer(file, deIndex, importBatchIndex, importBatchSize, deBuffer); })
			.and_then([&](bool) { return AtlasFitsDataUtilities::loadColumnIntoBuffer<double>(file, raProperMotionIndex, importBatchIndex, importBatchSize, raProperMotionBuffer); })
			.and_then([&](bool) { return AtlasFitsDataUtilities::loadColumnIntoBuffer<double>(file, decProperMotionIndex, importBatchIndex, importBatchSize, decProperMotionBuffer); })
			.and_then([&](bool) { return AtlasFitsDataUtilities::loadColumnIntoBuffer<float>(file, vMagIndex, importBatchIndex, importBatchSize, vMagBuffer); })
			.and_then([&](bool) { return AtlasFitsDataUtilities::loadColumnIntoBuffer<float>(file, bvIndex, importBatchIndex, importBatchSize, bvBuffer); });

		starObjectBuffer.clear();
		for (long i = 0; i < importBatchSize; ++i) {
			AtlasStar star;

			double raHours = 0.0, raMinutes = 0.0, raSeconds = 0.0;
			double deDegrees = 0.0, deMinutes = 0.0, deSeconds = 0.0;
			int deSign = 1;

			AtlasImportDefaultCatalog::getSexagesimalUnitsRA(raBuffer[i], raHours, raMinutes, raSeconds);
			AtlasImportDefaultCatalog::getSexagesimalUnitsDE(deBuffer[i], deSign, deDegrees, deMinutes, deSeconds);

			star.ra = AtlasProjectionMath::getRaRadians(raHours, raMinutes, raSeconds);
			star.de = AtlasProjectionMath::getDecRadians(deSign, deDegrees, deMinutes, deSeconds);
			star.pmRa = raProperMotionBuffer[i];
			star.pmDe = decProperMotionBuffer[i];
			star.mag = vMagBuffer[i];
			star.color = bvBuffer[i];

			starObjectBuffer.push_back(star);
		}

		loadCatalogResult = loadCatalogResult
			.and_then([&](bool) { return AtlasInsertBatchStarRenderData::insert(database, starObjectBuffer); });

		importBatchIndex += importBatchSize;
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

bool AtlasImportDefaultCatalog::getSexagesimalUnitsDE(std::string de, int& sign, double& deDegrees, double& deMinutes, double& deSeconds)
{
	sign = de.find('-') != std::string::npos ? -1 : 1;

	std::replace(de.begin(), de.end(), ':', ' ');
	std::replace(de.begin(), de.end(), '+', ' ');
	std::replace(de.begin(), de.end(), '-', ' ');

	std::stringstream stream(de);

	if (stream >> deDegrees >> deMinutes >> deSeconds) {
		return true;
	}

	return false;
}