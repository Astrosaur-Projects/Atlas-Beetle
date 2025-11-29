#include "AtlasCreateDatabase.h"
#include "AtlasDatabaseUtilities.h"
#include <wx/wx.h>

std::expected<bool, std::string> AtlasCreateDatabase::process() const
{
    sqlite3* atlasDatabase;

    std::string atlasDatabasePath = AtlasDatabaseUtilities::getPath();

    int resultCode = sqlite3_open(atlasDatabasePath.c_str(), &atlasDatabase);

    if (resultCode) {
        std::string errorMessage = std::format("Error opening database: {} (Code: {})", sqlite3_errmsg(atlasDatabase), resultCode);

        sqlite3_close(atlasDatabase);

        return std::unexpected<std::string>(errorMessage);
    }

    std::expected<bool, std::string> result = initCatalogDirectoryTable(atlasDatabase);

    sqlite3_close(atlasDatabase);

    return result;
}

std::expected<bool, std::string> AtlasCreateDatabase::initCatalogDirectoryTable(sqlite3* atlasDatabase) const
{
    char* sqlErrorBuffer = nullptr;

    std::string createCatalogDirectoryTableSql = "CREATE TABLE IF NOT EXISTS CatalogDirectory (name TEXT NOT NULL, source TEXT NOT NULL, type TEXT NOT NULL, isEnabled INTEGER NOT NULL, isInstalled INTEGER NOT NULL);";

    int resultCode = sqlite3_exec(atlasDatabase, createCatalogDirectoryTableSql.c_str(), nullptr, 0, &sqlErrorBuffer);

    if (resultCode) {
        std::string errorMessage = std::format("Error creating CatalogDirectory table: {} (Code: {})", sqlErrorBuffer, resultCode);

        sqlite3_free(sqlErrorBuffer);

        return std::unexpected<std::string>(errorMessage);
    }

    return true;
}