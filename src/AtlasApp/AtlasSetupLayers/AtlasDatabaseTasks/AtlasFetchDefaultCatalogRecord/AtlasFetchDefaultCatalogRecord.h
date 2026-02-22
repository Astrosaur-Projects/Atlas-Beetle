#ifndef ATLAS_FETCH_DEFAULT_CATALOG_RECORD_TASK_H
#define ATLAS_FETCH_DEFAULT_CATALOG_RECORD_TASK_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasFetchDefaultCatalogRecord
{
	std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> fetch(sqlite3* database);
};

#endif