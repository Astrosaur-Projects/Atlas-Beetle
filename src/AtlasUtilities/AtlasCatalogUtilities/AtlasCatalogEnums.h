#ifndef ATLAS_CATALOG_ENUMS_H
#define ATLAS_CATALOG_ENUMS_H

#include "AtlasCatalogTypeEnums.h"
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

	const std::map<AtlasCatalogEnums, const AtlasCatalogTypeEnums> AtlasCatalogTypes {
		{ AtlasCatalogEnums::CAT_SAO, AtlasCatalogTypeEnums::STAR },
		{ AtlasCatalogEnums::CAT_BSC5P, AtlasCatalogTypeEnums::STAR }
	};

	std::string getCatalogName(AtlasCatalogEnums catalog);
	std::string getCatalogDownloadPath(AtlasCatalogEnums catalog);
	AtlasCatalogTypeEnums getCatalogType(AtlasCatalogEnums catalog);
};

#endif