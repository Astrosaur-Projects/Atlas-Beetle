#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateTableStarRenderData/AtlasCreateTableStarRenderData.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateTableStarRenderData::create(sqlite3* database)
{
	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateTableStarRenderData::initStarRenderData(database); });

	return initDbResult;
}

std::expected<bool, std::string> AtlasCreateTableStarRenderData::initStarRenderData(sqlite3* database)
{
	std::string sql = R"(
        CREATE TABLE IF NOT EXISTS StarRenderData (
			id					INTEGER	PRIMARY	KEY,
			ra_rad				REAL	NOT NULL,
			dec_rad				REAL	NOT NULL,
			pm_ra				REAL	NOT NULL,
			pm_dec				REAL	NOT NULL,
			mag					REAL	NOT NULL,
			color_index			REAL	NOT NULL	DEFAULT 0,
			object_type			INTEGER	NOT NULL	DEFAULT 0,
			angular_size		REAL	NOT NULL	DEFAULT 0,
			orientation_angle	REAL
		);
	)";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error creating StarRenderData: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}