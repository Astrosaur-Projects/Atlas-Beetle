#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchTableCatalogDirectory/AtlasFetchTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> AtlasFetchTableCatalogDirectory::fetch(sqlite3* database)
{
	const std::string SELECT_FROM_CATALOG_DIRECTORY = "SELECT name, source, path, type FROM CatalogDirectory;";

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, SELECT_FROM_CATALOG_DIRECTORY);

	return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(prepareStatementResult.value(), database, AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement);
}