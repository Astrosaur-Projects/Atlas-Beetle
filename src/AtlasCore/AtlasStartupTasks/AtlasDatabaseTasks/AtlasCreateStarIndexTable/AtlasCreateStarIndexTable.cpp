#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateStarIndexTable/AtlasCreateStarIndexTable.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateStarIndexTable::create(sqlite3* database)
{
	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateStarIndexTable::initStarIndex(database); });

	return initDbResult;
}

std::expected<bool, std::string> AtlasCreateStarIndexTable::initStarIndex(sqlite3* database)
{
	std::string sql = R"(
        CREATE VIRTUAL TABLE StarIndex USING rtree(
		   id,
		   minX, maxX,
		   minY, maxY,
		   minZ, maxZ
		);
	)";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error creating StarIndex: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}