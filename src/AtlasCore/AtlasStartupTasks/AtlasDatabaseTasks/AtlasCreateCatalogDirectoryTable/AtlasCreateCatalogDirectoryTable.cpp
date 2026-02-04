#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateCatalogDirectoryTable/AtlasCreateCatalogDirectoryTable.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::create(sqlite3* database)
{
	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::initCatalogDirectory(database); });

	return initDbResult;
}

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::initCatalogDirectory(sqlite3* database)
{
	std::string sql = R"(
        CREATE TABLE IF NOT EXISTS CatalogDirectory (
            name        TEXT    NOT NULL,
            source      TEXT    NOT NULL,
			path		TEXT    NOT NULL,
            type        TEXT    NOT NULL,
            isEnabled   INTEGER NOT NULL DEFAULT 0,
            isInstalled INTEGER NOT NULL DEFAULT 0
        );
    )";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error creating CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}