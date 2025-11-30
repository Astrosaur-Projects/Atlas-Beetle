#include "AtlasDatabaseUtilities.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

wxString AtlasDatabaseUtilities::getDatabasePath()
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();
	
	wxString databaseDirectoryPath = AtlasDatabaseUtilities::getDirectoryPath();

	wxString databasePath = databaseDirectoryPath + wxFileName::GetPathSeparator() + "AtlasDatabase.db";

	return databasePath;
}

wxString AtlasDatabaseUtilities::getDirectoryPath()
{
    wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();
	
	wxString databaseDirectoryPath = wxStandardPaths.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + "AtlasDatabase";

    return databaseDirectoryPath;
}