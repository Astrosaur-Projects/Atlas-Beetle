#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchTableExists/AtlasFetchTableExists.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string > AtlasFetchTableExists::fetch(sqlite3* database, std::string tableName)
{
	std::expected<sqlite3_stmt*, std::string> fetchTableExistsResult = nullptr;

	return fetchTableExistsResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasFetchTableExists::prepareStatement(statement, database); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasFetchTableExists::bindParameter(statement, 1, tableName); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<bool, std::string> { return AtlasFetchTableExists::executeStatement(statement, database); });
}

std::expected<sqlite3_stmt*, std::string> AtlasFetchTableExists::prepareStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::string sql = "SELECT COUNT(type) FROM sqlite_master WHERE type = 'table' AND name = ?;";

	int resultCode = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, nullptr);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error preparing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<sqlite3_stmt*, std::string> AtlasFetchTableExists::bindParameter(sqlite3_stmt* statement, int index, std::string parameter)
{
	int resultCode = sqlite3_bind_text(statement, index, parameter.c_str(), -1, SQLITE_TRANSIENT);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error binding parameter to statement: {} (Code: {})", parameter, resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<bool, std::string> AtlasFetchTableExists::executeStatement(sqlite3_stmt* statement, sqlite3* database)
{
	int resultCode = SQLITE_OK;

	bool tableExists = false;

	while ((resultCode = sqlite3_step(statement)) == SQLITE_ROW) {
		tableExists = sqlite3_column_int(statement, 0);
	}

	sqlite3_finalize(statement);

	if (resultCode != SQLITE_DONE) {
		std::string errorMessage = std::format("Error fetching table existence: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return tableExists;
}