#include "AtlasCreateDatabase.h"
#include "AtlasDirectoryUtilities.h"
#include <format>
#include <wx/filename.h>

std::expected<bool, std::string> AtlasCreateDatabase::initialize() const
{
    sqlite3* database = nullptr;

    std::expected<bool, std::string> initDbResult = true;

    initDbResult = initDbResult
        .and_then([&](bool success) -> std::expected<bool, std::string> { return initDatabase(database); })
        .and_then([&](bool success) -> std::expected<bool, std::string> { return initCatalogDirectoryTable(database); });

    sqlite3_close(database);

    return initDbResult;
}

std::expected<bool, std::string> AtlasCreateDatabase::initDatabase(sqlite3* &database) const
{
    std::string databasePath = AtlasDirectoryUtilities::getDatabasePath().ToStdString();

    int resultCode = sqlite3_open(databasePath.c_str(), &database);

    if (resultCode) {
        std::string errorMessage = std::format("Error opening database: {} (Code: {})", sqlite3_errmsg(database), resultCode);

        sqlite3_close(database);

        return std::unexpected<std::string>(errorMessage);
    }

    return true;
}

std::expected<bool, std::string> AtlasCreateDatabase::initCatalogDirectoryTable(sqlite3* database) const
{
    std::string createTableSql = R"(
        CREATE TABLE IF NOT EXISTS CatalogDirectory (
            name        TEXT    NOT NULL,
            source      TEXT    NOT NULL,
            type        TEXT    NOT NULL,
            isEnabled   INTEGER NOT NULL,
            isInstalled INTEGER NOT NULL
        );
    )";

    int resultCode = sqlite3_exec(database, createTableSql.c_str(), nullptr, 0, nullptr);

    if (resultCode) {
        std::string errorMessage = std::format("Error creating CatalogDirectory table: {} (Code: {})", sqlite3_errmsg(database), resultCode);

        return std::unexpected<std::string>(errorMessage);
    }

    return true;
}