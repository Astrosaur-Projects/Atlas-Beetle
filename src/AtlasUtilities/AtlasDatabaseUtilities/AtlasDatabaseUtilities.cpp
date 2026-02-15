#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> AtlasDatabaseUtilities::open()
{
	sqlite3* database = nullptr;

	std::string path = AtlasDirectoryUtilities::getDatabasePath();

	int resultCode = sqlite3_open(path.c_str(), &database);

	if (resultCode) {
		std::string error = std::format("Error opening database: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(error);
	}

	return AtlasDatabaseUtilities::MemorySafeDatabase(database);
}

std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> AtlasDatabaseUtilities::prepareStatement(sqlite3* database, std::string sql)
{
	sqlite3_stmt* statement = nullptr;

	int resultCode = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, nullptr);

	if (resultCode) {
		std::string error = std::format("Error preparing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(error);
	}

	return AtlasDatabaseUtilities::MemorySafeStatement(statement);
}

std::expected<bool, std::string> AtlasDatabaseUtilities::execute(sqlite3_stmt* statement, sqlite3* database)
{
	int resultCode;

	while ((resultCode = sqlite3_step(statement)) == SQLITE_ROW) { }

	sqlite3_reset(statement);

	if (resultCode != SQLITE_DONE) {
		std::string error = std::format("Error executing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(error);
	}

	return true;
}