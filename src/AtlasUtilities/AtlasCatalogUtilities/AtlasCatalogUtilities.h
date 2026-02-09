#ifndef ATLAS_CATALOG_UTILS_H
#define ATLAS_CATALOG_UTILS_H

#include <string>

namespace AtlasCatalogUtilities
{
	enum class AtlasCatalogEnums : int
	{
		CAT_BSC5P,
	};

	enum class AtlasCatalogTypeEnums : int
	{
		STAR,
	};

	struct AtlasCatalogObject
	{
		AtlasCatalogEnums id;

		AtlasCatalogTypeEnums type;

		std::string name;

		std::string source;
	};

	struct CatalogRecord
	{
		std::string name;

		std::string source;

		std::string path;

		std::string type;

		bool isEnabled;

		bool isInstalled;
	};

	AtlasCatalogObject getDefaultCatalogObject();
	std::string getCatalogFilePath(AtlasCatalogObject catalog);
};

#endif