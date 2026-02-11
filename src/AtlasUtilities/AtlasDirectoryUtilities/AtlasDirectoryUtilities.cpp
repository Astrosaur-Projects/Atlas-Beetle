#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <string>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/string.h>

std::string AtlasDirectoryUtilities::getDatabasePath()
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();

	wxString databaseDirectoryPath = AtlasDirectoryUtilities::getDirectoryPath(AtlasDirectoryEnums::DIR_DATABASE);

	wxString databasePath = databaseDirectoryPath + wxFileName::GetPathSeparator() + "AtlasDatabase.db";

	return databasePath.ToStdString();
}

std::string AtlasDirectoryUtilities::getDirectoryPath(AtlasDirectoryEnums directory)
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();

	wxString databaseDirectoryPath = wxStandardPaths.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + AtlasDirectoryUtilities::getDirectoryName(directory);

	return databaseDirectoryPath.ToStdString();
}

std::string AtlasDirectoryUtilities::getDirectoryName(AtlasDirectoryEnums directory)
{
	switch (directory) {
		case AtlasDirectoryEnums::DIR_CATALOGS: return "AtlasCatalogs";
		case AtlasDirectoryEnums::DIR_DATABASE: return "AtlasDatabase";
		case AtlasDirectoryEnums::DIR_PLUGINS:	return "AtlasPlugins";
		default: return "";
	}
}