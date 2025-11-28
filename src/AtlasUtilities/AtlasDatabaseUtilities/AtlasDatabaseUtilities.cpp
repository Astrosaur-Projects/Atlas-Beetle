#include "AtlasDatabaseUtilities.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

std::string AtlasDatabaseUtilities::getPath()
{
	wxStandardPaths& wxStandardPaths = wxStandardPaths::Get();

	wxString atlasDatabaseDirectory = wxStandardPaths.GetUserLocalDataDir() + wxFileName::GetPathSeparator() + "AtlasDatabase";

	wxString atlasDatabasePath = atlasDatabaseDirectory + wxFileName::GetPathSeparator() + "AtlasDatabase.db";

	return atlasDatabasePath.ToStdString();
}

bool AtlasDatabaseUtilities::isInitialized()
{
    wxString atlasDatabasePath = AtlasDatabaseUtilities::getPath();

    wxFileName atlasDatabaseFile(atlasDatabasePath);

    if (!atlasDatabaseFile.IsOk()) {
        printf("Invalid filename: %s", (const char*)atlasDatabasePath.mb_str());

        return false;
    }

    if (!atlasDatabaseFile.FileExists()) {
        printf("File does not exist: %s", (const char*)atlasDatabasePath.mb_str());

        return false;
    }

	return true;
}