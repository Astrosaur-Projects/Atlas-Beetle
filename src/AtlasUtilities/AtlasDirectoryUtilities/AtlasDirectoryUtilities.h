#ifndef ATLAS_DIRECTORY_UTILS_H
#define ATLAS_DIRECTORY_UTILS_H

#include "AtlasDirectoryEnums.h"
#include <wx/string.h>

namespace AtlasDirectoryUtilities
{
	wxString getDatabasePath();
	wxString getDirectoryPath(AtlasDirectoryEnums directory);
};

#endif