#ifndef ATLAS_QUERY_CATALOG_DIRECTORY_H
#define ATLAS_QUERY_CATALOG_DIRECTORY_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <string>
#include <vector>

class AtlasQueryCatalogDirectory
{
public:
	AtlasQueryCatalogDirectory();

	std::vector<AtlasCatalogUtilities::CatalogRecord> Query();

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;
	AtlasDatabaseUtilities::MemorySafeStatement statement;

private:
	const std::string QUERY_STAR_RENDER_DATA = R"(
        SELECT * FROM CatalogDirectory;
    )";
};

#endif