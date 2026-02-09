#ifndef ATLAS_FETCH_DEFAULT_CATALOG_TASK_H
#define ATLAS_FETCH_DEFAULT_CATALOG_TASK_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasFetchDefaultCatalogRecord
{
	std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> fetch(sqlite3* database);
	std::expected<sqlite3_stmt*, std::string> prepareStatement(sqlite3_stmt* statement, sqlite3* database);
	std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> executeStatement(sqlite3_stmt* statement, sqlite3* database);
};

#endif