#include "AtlasDirectoryEnums.h"
#include "AtlasDirectoryUtilities.h"
#include <string>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/string.h>

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

	wxString databaseDirectoryPath = wxStandardPaths.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + AtlasDirectoryUtilities::getDirectoryString(directory);

	return databaseDirectoryPath;
}

std::string AtlasDirectoryUtilities::getDirectoryString(AtlasDirectoryEnums directory)
{
	auto directoryString = AtlasDirectoryUtilities::AtlasDirectoryStrings.find(directory);

	return directoryString == AtlasDirectoryUtilities::AtlasDirectoryStrings.end() ? "Undefined" : directoryString->second;
}