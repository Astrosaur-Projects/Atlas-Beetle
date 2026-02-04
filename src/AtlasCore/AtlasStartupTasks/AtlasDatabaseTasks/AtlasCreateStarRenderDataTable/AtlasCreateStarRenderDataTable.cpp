#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateStarRenderDataTable/AtlasCreateStarRenderDataTable.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateStarRenderDataTable::create(sqlite3* database)
{
	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateStarRenderDataTable::initStarRenderData(database); });

	return initDbResult;
}

std::expected<bool, std::string> AtlasCreateStarRenderDataTable::initStarRenderData(sqlite3* database)
{
	std::string sql = R"(
        CREATE TABLE StarRenderData (
		   id			INTEGER	PRIMARY	KEY,
		   ra_rad		REAL	NOT NULL,
		   dec_rad		REAL	NOT NULL,
		   pm_ra		REAL	NOT NULL,
		   pm_dec		REAL	NOT NULL,
		   mag			REAL	NOT NULL,
		   color_index	REAL,
		   object_type	INTEGER	NOT NULL,
		   angular_size	REAL,
		);
	)";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error creating StarRenderData: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}