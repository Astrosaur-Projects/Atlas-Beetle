#include "AtlasApp/AtlasStartupLayers/AtlasSetupDefaultCatalog/AtlasSetupDefaultCatalog.h"
#include "AtlasCore/AtlasMath/AtlasMath.h"
#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include "AtlasUtilities/AtlasFitsDataUtilities/AtlasFitsDataUtilities.h"
#include <algorithm>
#include <cfitsio/fitsio.h>
#include <expected>
#include <sqlite3.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

void AtlasSetupDefaultCatalog::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());
}

std::expected<bool, std::string> AtlasSetupDefaultCatalog::Start()
{
	return AtlasDatabaseUtilities::prepareStatement(database.get(), FETCH_DEFAULT_CATALOG)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(statement.get(), database.get(), AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement); })
		.transform([](std::vector<AtlasCatalogUtilities::CatalogRecord> records) { return records.front(); })
		.and_then([&](AtlasCatalogUtilities::CatalogRecord catalog) { return LoadCatalog(catalog); });
}

std::expected<bool, std::string> AtlasSetupDefaultCatalog::LoadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog)
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

	std::vector<std::string> raBuffer(STAR_IMPORT_BATCH_SIZE);
	std::vector<std::string> deBuffer(STAR_IMPORT_BATCH_SIZE);
	std::vector<double> raProperMotionBuffer(STAR_IMPORT_BATCH_SIZE);
	std::vector<double> decProperMotionBuffer(STAR_IMPORT_BATCH_SIZE);
	std::vector<float> vMagBuffer(STAR_IMPORT_BATCH_SIZE);
	std::vector<float> bvBuffer(STAR_IMPORT_BATCH_SIZE);

	std::vector<AtlasStar> starObjectBuffer;
	starObjectBuffer.reserve(STAR_IMPORT_BATCH_SIZE);

	long importBatchIndex = 1;

	while (loadCatalogResult.has_value() && (importBatchIndex <= totalCatalogRows)) {
		long importBatchSize = std::min(STAR_IMPORT_BATCH_SIZE, totalCatalogRows - importBatchIndex + 1);

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

			if (raProperMotionBuffer[i] == 0.0 && decProperMotionBuffer[i] == 0.0) { continue; }

			double raHours = 0.0, raMinutes = 0.0, raSeconds = 0.0;
			double deDegrees = 0.0, deMinutes = 0.0, deSeconds = 0.0;
			int deSign = 1;

			GetSexagesimalUnitsRA(raBuffer[i], raHours, raMinutes, raSeconds);
			GetSexagesimalUnitsDE(deBuffer[i], deSign, deDegrees, deMinutes, deSeconds);

			star.ra = AtlasMath::getRaRadians(raHours, raMinutes, raSeconds);
			star.de = AtlasMath::getDecRadians(deSign, deDegrees, deMinutes, deSeconds);
			star.pmRa = raProperMotionBuffer[i];
			star.pmDe = decProperMotionBuffer[i];
			star.mag = vMagBuffer[i];
			star.color = bvBuffer[i];

			starObjectBuffer.push_back(star);
		}

		loadCatalogResult = loadCatalogResult
			.and_then([&](bool) { return Insert(starObjectBuffer); });

		importBatchIndex += importBatchSize;
	}

	return loadCatalogResult;
}

std::expected<bool, std::string> AtlasSetupDefaultCatalog::Insert(std::vector<AtlasStar> buffer)
{
	if (buffer.empty()) {
		return true;
	}

	std::expected<bool, std::string> insertBatchDataResult = true;

	insertBatchDataResult = insertBatchDataResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database.get(), BEGIN_TRANSACTION); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database.get()); })
		.and_then([&](bool) { return InsertStarRenderData(buffer); });

	if (!insertBatchDataResult.has_value()) {
		std::ignore = AtlasDatabaseUtilities::prepareStatement(database.get(), ROLLBACK_TRANSACTION)
			.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database.get()); });

		return std::unexpected<std::string>(insertBatchDataResult.error());
	}

	return AtlasDatabaseUtilities::prepareStatement(database.get(), COMMIT_TRANSACTION)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database.get()); });
}

std::expected<bool, std::string> AtlasSetupDefaultCatalog::InsertStarRenderData(std::vector<AtlasStar> buffer)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareInsertStatementResult = AtlasDatabaseUtilities::prepareStatement(database.get(), INSERT_STAR_RENDER_DATA_STATEMENT);

	if (!prepareInsertStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareInsertStatementResult.error());
	}

	sqlite3_stmt* statement = prepareInsertStatementResult.value().get();

	std::expected<bool, std::string> insertStarRenderDataResult = true;

	for (const auto& star : buffer) {
		insertStarRenderDataResult = insertStarRenderDataResult
			.and_then([&](bool) { return AtlasDatabaseUtilities::bindStatementParameters(statement, star.ra, star.de, star.pmRa, star.pmDe, star.mag, star.color, (int)AtlasCatalogUtilities::AtlasCatalogTypeEnums::STAR); })
			.and_then([&](bool) { return AtlasDatabaseUtilities::execute(statement, database.get()); });

		if (!insertStarRenderDataResult.has_value()) { break; }
	}

	return insertStarRenderDataResult;
}

bool AtlasSetupDefaultCatalog::GetSexagesimalUnitsRA(std::string ra, double& raHours, double& raMinutes, double& raSeconds)
{
	std::replace(ra.begin(), ra.end(), ':', ' ');

	std::stringstream stream(ra);

	if (stream >> raHours >> raMinutes >> raSeconds) {
		return true;
	}

	return false;
}

bool AtlasSetupDefaultCatalog::GetSexagesimalUnitsDE(std::string de, int& sign, double& deDegrees, double& deMinutes, double& deSeconds)
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