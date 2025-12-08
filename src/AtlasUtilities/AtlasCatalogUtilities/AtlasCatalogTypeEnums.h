#ifndef ATLAS_CATALOG_TYPE_ENUMS_H
#define ATLAS_CATALOG_TYPE_ENUMS_H

#include <map>
#include <string>

namespace AtlasCatalogUtilities
{
	enum class AtlasCatalogTypeEnums
	{
		PLANET,
		STAR,
		DSO,
	};

	const std::map<AtlasCatalogTypeEnums, const std::string> AtlasCatalogTypeStrings {
		{ AtlasCatalogTypeEnums::PLANET, "Planet" },
		{ AtlasCatalogTypeEnums::STAR, "Star" },
		{ AtlasCatalogTypeEnums::DSO, "DSO" }
	};

	std::string getCatalogTypeString(AtlasCatalogTypeEnums type);
};

#endif