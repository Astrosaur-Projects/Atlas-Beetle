#include "AtlasCreateCatalogDirectoryTable.h"
#include <format>

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::create(sqlite3* database)
{
    std::string createSql = R"(
        CREATE TABLE IF NOT EXISTS CatalogDirectory (
            name        TEXT    NOT NULL,
            source      TEXT    NOT NULL,
            type        TEXT    NOT NULL,
            isEnabled   INTEGER NOT NULL,
            isInstalled INTEGER NOT NULL
        );
    )";

    int resultCode = sqlite3_exec(database, createSql.c_str(), nullptr, 0, nullptr);

    if (resultCode) {
        std::string errorMessage = std::format("Error creating CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

        return std::unexpected<std::string>(errorMessage);
    }

    return true;
}