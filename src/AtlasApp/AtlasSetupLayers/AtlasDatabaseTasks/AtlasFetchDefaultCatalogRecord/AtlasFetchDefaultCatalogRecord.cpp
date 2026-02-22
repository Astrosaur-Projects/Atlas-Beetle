#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasFetchDefaultCatalogRecord/AtlasFetchDefaultCatalogRecord.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> AtlasFetchDefaultCatalogRecord::fetch(sqlite3* database)
{
	const std::string FETCH_DEFAULT_CATALOG = "SELECT * FROM CatalogDirectory WHERE id = 0";

	return AtlasDatabaseUtilities::prepareStatement(database, FETCH_DEFAULT_CATALOG)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(statement.get(), database, AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement); })
		.transform([](std::vector<AtlasCatalogUtilities::CatalogRecord> records) { return records.front(); });
}