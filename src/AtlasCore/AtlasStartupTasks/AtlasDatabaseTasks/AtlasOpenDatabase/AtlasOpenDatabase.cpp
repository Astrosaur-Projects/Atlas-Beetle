#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasOpenDatabase/AtlasOpenDatabase.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasOpenDatabase::open(sqlite3*& database)
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