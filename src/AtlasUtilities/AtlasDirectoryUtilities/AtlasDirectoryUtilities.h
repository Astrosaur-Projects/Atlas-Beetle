#ifndef ATLAS_DIRECTORY_UTILS_H
#define ATLAS_DIRECTORY_UTILS_H

#include <string>
#include <wx/string.h>

namespace AtlasDirectoryUtilities
{
	enum class AtlasDirectoryEnums : int
	{
		DIR_CATALOGS,
		DIR_PLUGINS,
		DIR_DATABASE
	};

	wxString getDatabasePath();
	wxString getDirectoryPath(AtlasDirectoryEnums directory);
	std::string getDirectoryString(AtlasDirectoryEnums directory);
};

#endif