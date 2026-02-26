#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <string>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/string.h>

std::string AtlasDirectoryUtilities::GetDatabasePath()
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();

	wxString databaseDirectoryPath = AtlasDirectoryUtilities::GetDirectoryPath(AtlasDirectoryEnums::DIR_DATABASE);

	wxString databasePath = databaseDirectoryPath + wxFileName::GetPathSeparator() + "AtlasDatabase.db";

	return databasePath.ToStdString();
}

std::string AtlasDirectoryUtilities::GetDirectoryPath(AtlasDirectoryEnums directory)
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();

	wxString databaseDirectoryPath = wxStandardPaths.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + AtlasDirectoryUtilities::GetDirectoryName(directory);

	return databaseDirectoryPath.ToStdString();
}

std::string AtlasDirectoryUtilities::GetDirectoryName(AtlasDirectoryEnums directory)
{
	switch (directory) {
		case AtlasDirectoryEnums::DIR_CATALOGS: return "AtlasCatalogs";
		case AtlasDirectoryEnums::DIR_DATABASE: return "AtlasDatabase";
		case AtlasDirectoryEnums::DIR_PLUGINS: return "AtlasPlugins";
		default: return "";
	}
}