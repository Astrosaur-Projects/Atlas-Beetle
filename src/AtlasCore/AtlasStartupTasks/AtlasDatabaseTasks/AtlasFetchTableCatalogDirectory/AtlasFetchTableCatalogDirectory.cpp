#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchTableCatalogDirectory/AtlasFetchTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> AtlasFetchTableCatalogDirectory::fetch(sqlite3* database)
{
	const std::string SELECT_FROM_CATALOG_DIRECTORY = "SELECT id, name, source, path, type, isEnabled, isInstalled FROM CatalogDirectory;";

	return AtlasDatabaseUtilities::prepareStatement(database, SELECT_FROM_CATALOG_DIRECTORY)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) -> std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> { return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(statement.get(), database, AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement); });
}