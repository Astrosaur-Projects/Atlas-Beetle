#ifndef ATLAS_FETCH_TABLE_CATALOG_DIRECTORY_TASK_H
#define ATLAS_FETCH_TABLE_CATALOG_DIRECTORY_TASK_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace AtlasFetchTableCatalogDirectory
{
	std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> fetch(sqlite3* database);
};

#endif