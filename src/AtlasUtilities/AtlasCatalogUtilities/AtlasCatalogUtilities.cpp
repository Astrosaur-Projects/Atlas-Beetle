#include "AtlasCatalogUtilities.h"
#include "AtlasCatalogEnums.h"
#include "AtlasCatalogTypeEnums.h"

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

std::string AtlasCatalogUtilities::getCatalogTypeString(AtlasCatalogTypeEnums type)
{
	auto catalogTypeString = AtlasCatalogUtilities::AtlasCatalogTypeStrings.find(type);

	return catalogTypeString == AtlasCatalogUtilities::AtlasCatalogTypeStrings.end() ? "" : catalogTypeString->second;
}