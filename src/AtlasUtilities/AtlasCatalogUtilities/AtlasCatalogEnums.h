#ifndef ATLAS_CATALOG_ENUMS_H
#define ATLAS_CATALOG_ENUMS_H

#include <map>
#include <string>

namespace AtlasCatalogUtilities
{
	enum class AtlasCatalogEnums
	{
		CAT_SAO,
		CAT_BSC5P,
	};

	const std::map<AtlasCatalogEnums, const std::string> AtlasCatalogNames {
		{ AtlasCatalogEnums::CAT_SAO, "Smithsonian Astrophysical Observatory Star Catalog" },
		{ AtlasCatalogEnums::CAT_BSC5P, "Bright Star Catalog" }
	};

	const std::map<AtlasCatalogEnums, const std::string> AtlasCatalogDownloadPaths {
		{ AtlasCatalogEnums::CAT_SAO, "https://cdsarc.cds.unistra.fr/ftp/cats/I/131A/sao.dat.gz" },
		{ AtlasCatalogEnums::CAT_BSC5P, "https://cdsarc.cds.unistra.fr/ftp/cats/V/50/catalog.gz" }
	};

	std::string getCatalogName(AtlasCatalogEnums catalog);
	std::string getCatalogDownloadPath(AtlasCatalogEnums catalog);
};

#endif