#include "AtlasApp/AtlasQueryObjects/AtlasQueryGraphicsConfig/AtlasQueryGraphicsConfig.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

AtlasQueryGraphicsConfig::AtlasQueryGraphicsConfig()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::Open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), QUERY_GRAPHICS_CONFIG);

	if (!prepareStatementResult.has_value()) {
		throw std::runtime_error(prepareStatementResult.error());
	}

	statement = std::move(prepareStatementResult.value());
}

std::expected<std::vector<AtlasQueryGraphicsConfig::GraphicsConfigRecord>, std::string> AtlasQueryGraphicsConfig::Query()
{
	const auto initializeGraphicsConfigRecordFromSQLStatement = [](sqlite3_stmt* statement) -> AtlasQueryGraphicsConfig::GraphicsConfigRecord {
		return AtlasQueryGraphicsConfig::GraphicsConfigRecord {
			.id = sqlite3_column_int(statement, 0),
			.pointSize = (float)sqlite3_column_double(statement, 1),
			.magnitudeLimit = (float)sqlite3_column_double(statement, 2)
		};
	};

	return AtlasDatabaseUtilities::Query<AtlasQueryGraphicsConfig::GraphicsConfigRecord>(statement.get(), database.get(), initializeGraphicsConfigRecordFromSQLStatement);
}