#include "AtlasApp/AtlasQueryObjects/AtlasQueryLocationConfig/AtlasQueryLocationConfig.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

AtlasQueryLocationConfig::AtlasQueryLocationConfig()
{
	InitializeDatabase();

	fetchStatement = InitializeStatement(FETCH_LOCATION_CONFIG);
	updateStatement = InitializeStatement(UPDATE_LOCATION_CONFIG);
}

void AtlasQueryLocationConfig::InitializeDatabase()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::Open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());
}

AtlasDatabaseUtilities::MemorySafeStatement AtlasQueryLocationConfig::InitializeStatement(std::string query)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), query);

	if (!prepareStatementResult.has_value()) {
		throw std::runtime_error(prepareStatementResult.error());
	}

	return std::move(prepareStatementResult.value());
}

std::expected<std::vector<AtlasQueryLocationConfig::LocationConfigRecord>, std::string> AtlasQueryLocationConfig::Query()
{
	const auto initializeLocationConfigRecordFromSQLStatement = [](sqlite3_stmt* statement) -> AtlasQueryLocationConfig::LocationConfigRecord {
		return AtlasQueryLocationConfig::LocationConfigRecord {
			.id = sqlite3_column_int(statement, 0),
			.latitude = (float)sqlite3_column_double(statement, 1),
			.longitude = (float)sqlite3_column_double(statement, 2),
			.elevation = (float)sqlite3_column_double(statement, 3)
		};
	};

	return AtlasDatabaseUtilities::Query<AtlasQueryLocationConfig::LocationConfigRecord>(fetchStatement.get(), database.get(), initializeLocationConfigRecordFromSQLStatement);
}