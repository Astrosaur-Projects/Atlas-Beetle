#include "AtlasApp/AtlasQueryObjects/AtlasQueryCatalogDirectory/AtlasQueryCatalogDirectory.h"
#include <AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h>
#include <AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h>
#include <expected>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

AtlasQueryCatalogDirectory::AtlasQueryCatalogDirectory() : database(nullptr), statement(nullptr)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database.get(), QUERY_STAR_RENDER_DATA);

	if (!prepareStatementResult.has_value()) {
		throw std::runtime_error(prepareStatementResult.error());
	}

	statement = std::move(prepareStatementResult.value());
}

std::vector<AtlasCatalogUtilities::CatalogRecord> AtlasQueryCatalogDirectory::Query()
{
	const auto initializeCatalogRecordFromSQLStatement = [](sqlite3_stmt* statement) -> AtlasCatalogUtilities::CatalogRecord {
		return AtlasCatalogUtilities::CatalogRecord {
			.id = sqlite3_column_int(statement, 0),
			.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)),
			.source = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)),
			.path = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)),
			.type = sqlite3_column_int(statement, 4),
			.isEnabled = (bool)sqlite3_column_int(statement, 5),
			.isInstalled = (bool)sqlite3_column_int(statement, 6)
		};
	};

	std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> queryStarRenderDataResult = AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(statement.get(), database.get(), initializeCatalogRecordFromSQLStatement);

	if (!queryStarRenderDataResult.has_value()) {
		return std::vector<AtlasCatalogUtilities::CatalogRecord>();
	}

	return queryStarRenderDataResult.value();
}
