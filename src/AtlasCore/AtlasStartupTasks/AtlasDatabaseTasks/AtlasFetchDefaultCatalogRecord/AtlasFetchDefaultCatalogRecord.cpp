#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDefaultCatalogRecord/AtlasFetchDefaultCatalogRecord.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> AtlasFetchDefaultCatalogRecord::fetch(sqlite3* database)
{
	const std::string FETCH_DEFAULT_CATALOG = "SELECT * FROM CatalogDirectory WHERE id = 0";

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, FETCH_DEFAULT_CATALOG);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statement = prepareStatementResult.value().get();

	return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(statement, database, AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement)
		.transform([](std::vector<AtlasCatalogUtilities::CatalogRecord> records) { return records.front(); });
}