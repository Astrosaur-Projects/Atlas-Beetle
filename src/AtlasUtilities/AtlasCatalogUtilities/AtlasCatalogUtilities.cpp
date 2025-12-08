#include "AtlasCatalogUtilities.h"
#include "AtlasCatalogEnums.h"

std::string AtlasCatalogUtilities::getCatalogName(AtlasCatalogEnums catalog)
{
	auto name = AtlasCatalogUtilities::AtlasCatalogNames.find(catalog);

	return name == AtlasCatalogUtilities::AtlasCatalogNames.end() ? "" : name->second;
}

std::string AtlasCatalogUtilities::getCatalogDownloadPath(AtlasCatalogEnums catalog)
{
	auto path = AtlasCatalogUtilities::AtlasCatalogDownloadPaths.find(catalog);

	return path == AtlasCatalogUtilities::AtlasCatalogDownloadPaths.end() ? "" : path->second;
}