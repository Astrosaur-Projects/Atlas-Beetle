#include "AtlasCatalogUtilities.h"
#include "AtlasCatalogEnums.h"
#include "AtlasCatalogTypeEnums.h"

std::string AtlasCatalogUtilities::getCatalogName(AtlasCatalogEnums catalog)
{
	auto name = AtlasCatalogUtilities::AtlasCatalogNames.find(catalog);

	return name == AtlasCatalogUtilities::AtlasCatalogNames.end() ? "Undefined" : name->second;
}

std::string AtlasCatalogUtilities::getCatalogDownloadPath(AtlasCatalogEnums catalog)
{
	auto path = AtlasCatalogUtilities::AtlasCatalogDownloadPaths.find(catalog);

	return path == AtlasCatalogUtilities::AtlasCatalogDownloadPaths.end() ? "Undefined" : path->second;
}

AtlasCatalogUtilities::AtlasCatalogTypeEnums AtlasCatalogUtilities::getCatalogType(AtlasCatalogEnums catalog)
{
	auto type = AtlasCatalogUtilities::AtlasCatalogTypes.find(catalog);

	return type == AtlasCatalogUtilities::AtlasCatalogTypes.end() ? AtlasCatalogTypeEnums::STAR : type->second;
}

std::string AtlasCatalogUtilities::getCatalogTypeString(AtlasCatalogTypeEnums type)
{
	auto typeString = AtlasCatalogUtilities::AtlasCatalogTypeStrings.find(type);

	return typeString == AtlasCatalogUtilities::AtlasCatalogTypeStrings.end() ? "Undefined" : typeString->second;
}