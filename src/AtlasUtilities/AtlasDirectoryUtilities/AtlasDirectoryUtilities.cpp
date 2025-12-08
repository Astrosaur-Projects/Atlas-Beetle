#include "AtlasDirectoryUtilities.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

wxString AtlasDirectoryUtilities::getDatabasePath()
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();
	
	wxString databaseDirectoryPath = AtlasDirectoryUtilities::getDirectoryPath(AtlasDirectoryEnums::DIR_DATABASE);

	wxString databasePath = databaseDirectoryPath + wxFileName::GetPathSeparator() + "AtlasDatabase.db";

	return databasePath;
}

wxString AtlasDirectoryUtilities::getDirectoryPath(AtlasDirectoryEnums directory)
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();

	wxString databaseDirectoryPath = wxStandardPaths.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + AtlasDirectoryUtilities::getDirectoryEnumString(directory);

	return databaseDirectoryPath;
}

std::string AtlasDirectoryUtilities::getDirectoryEnumString(AtlasDirectoryEnums directory)
{
	auto directoryString = AtlasDirectoryUtilities::AtlasDirectoryStrings.find(directory);

	return directoryString == AtlasDirectoryUtilities::AtlasDirectoryStrings.end() ? "" : directoryString->second;
}