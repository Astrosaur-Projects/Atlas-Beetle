#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasInsertBatchStarRenderData/AtlasInsertBatchStarRenderData.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <tuple>
#include <vector>

std::expected<bool, std::string> AtlasInsertBatchStarRenderData::insert(sqlite3* database, std::vector<AtlasStar> buffer)
{
	if (!database || buffer.empty()) {
		return true;
	}

	std::string BEGIN_TRANSACTION = "BEGIN TRANSACTION;";

	std::expected<bool, std::string> insertBatchDataResult = true;

	insertBatchDataResult = insertBatchDataResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, BEGIN_TRANSACTION); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); })
		.and_then([&](bool) { return AtlasInsertBatchStarRenderData::insertStarRenderData(database, buffer); });

	if (!insertBatchDataResult.has_value()) {
		std::string ROLLBACK_TRANSACTION = "ROLLBACK;";

		std::ignore = AtlasDatabaseUtilities::prepareStatement(database, ROLLBACK_TRANSACTION)
			.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

		return std::unexpected<std::string>(insertBatchDataResult.error());
	}

	std::string COMMIT_TRANSACTION = "COMMIT;";

	return AtlasDatabaseUtilities::prepareStatement(database, COMMIT_TRANSACTION)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });
}

std::expected<bool, std::string> AtlasInsertBatchStarRenderData::insertStarRenderData(sqlite3* database, std::vector<AtlasStar> buffer)
{
	std::string INSERT_STAR_RENDER_DATA_STATEMENT = "INSERT OR IGNORE INTO StarRenderData (ra_rad, dec_rad, pm_ra, pm_dec, mag, color_index, object_type) VALUES (?, ?, ?, ?, ?, ?, ?);";

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareInsertStatementResult = AtlasDatabaseUtilities::prepareStatement(database, INSERT_STAR_RENDER_DATA_STATEMENT);

	if (!prepareInsertStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareInsertStatementResult.error());
	}

	sqlite3_stmt* statement = prepareInsertStatementResult.value().get();

	std::expected<bool, std::string> insertStarRenderDataResult = true;

	for (const auto& star : buffer) {
		insertStarRenderDataResult = insertStarRenderDataResult
			.and_then([&](bool) { return AtlasDatabaseUtilities::bindStatementParameters(statement, star.ra, star.de, star.pmRa, star.pmDe, star.mag, star.color, (int)AtlasCatalogUtilities::AtlasCatalogTypeEnums::STAR); })
			.and_then([&](bool) { return AtlasDatabaseUtilities::execute(statement, database); });

		if (!insertStarRenderDataResult.has_value()) { break; }
	}

	return insertStarRenderDataResult;
}
