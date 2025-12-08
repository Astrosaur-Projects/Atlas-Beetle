#ifndef ATLAS_DIRECTORY_UTILS_H
#define ATLAS_DIRECTORY_UTILS_H

#include <map>
#include <wx/string.h>
#include "AtlasDirectoryEnums.h"

namespace AtlasDirectoryUtilities
{
	wxString getDatabasePath();
	wxString getDirectoryPath(AtlasDirectoryEnums directory);
};

#endif