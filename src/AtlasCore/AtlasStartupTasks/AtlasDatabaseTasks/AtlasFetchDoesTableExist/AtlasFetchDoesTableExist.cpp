#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDoesTableExist/AtlasFetchDoesTableExist.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<bool, std::string> AtlasFetchDoesTableExist::fetch(sqlite3* database, std::string table)
{
	const std::string FETCH_DOES_TABLE_EXIST = "SELECT COUNT(type) FROM sqlite_master WHERE type = 'table' AND name = ?;";

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, FETCH_DOES_TABLE_EXIST);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statement = prepareStatementResult.value().get();

	const auto initializeIntFromSQLStatement = [](sqlite3_stmt* statement) -> int { return sqlite3_column_int(statement, 0); };

	std::expected<bool, std::string> fetchTableExistResult = true;

	fetchTableExistResult = fetchTableExistResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasDatabaseUtilities::bindStatementParameters(statement, table); })
		.and_then([&](bool success) -> std::expected<std::vector<int>, std::string> { return AtlasDatabaseUtilities::query<int>(statement, database, initializeIntFromSQLStatement); })
		.transform([](std::vector<int> records) { return records.front() > 0; });

	return fetchTableExistResult;
}