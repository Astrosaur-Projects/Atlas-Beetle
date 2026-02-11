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

	return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(prepareStatementResult.value(), database, AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement)
		.transform([](std::vector<AtlasCatalogUtilities::CatalogRecord> records) { return records.front(); });
}