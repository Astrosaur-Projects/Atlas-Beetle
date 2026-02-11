#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <regex>
#include <string>
#include <wx/filename.h>
#include <wx/string.h>

AtlasCatalogUtilities::AtlasCatalogObject AtlasCatalogUtilities::getDefaultCatalogObject()
{
	return AtlasCatalogUtilities::AtlasCatalogObject {
		AtlasCatalogEnums::CAT_BSC5P,
		AtlasCatalogTypeEnums::STAR,
		"Bright Star Catalogue, 5th Revised Ed. (Hoffleit+, 1991)",
		"https://vizier.cds.unistra.fr/viz-bin/asu-fits?-source=V/50/catalog"
	};
}

std::string AtlasCatalogUtilities::getCatalogFilePath(AtlasCatalogUtilities::AtlasCatalogObject catalog)
{
	std::string fileName = std::regex_replace(catalog.name, std::regex("[^a-zA-Z0-9._-]"), "");

	wxString path = wxString(AtlasDirectoryUtilities::getDirectoryPath(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_CATALOGS))
		+ wxFileName::GetPathSeparator()
		+ fileName
		+ ".fits";

	return path.ToStdString();
}