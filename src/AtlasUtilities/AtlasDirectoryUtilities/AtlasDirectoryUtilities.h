#ifndef ATLAS_DIRECTORY_UTILS_H
#define ATLAS_DIRECTORY_UTILS_H

#include <map>
#include <wx/string.h>

namespace AtlasDirectoryUtilities
{
	enum class AtlasDirectoryEnums
	{
		DIR_CATALOGS,
		DIR_PLUGINS,
		DIR_DATABASE
	};

	const std::map<AtlasDirectoryEnums, const std::string> AtlasDirectoryStrings {
		{ AtlasDirectoryEnums::DIR_DATABASE, "AtlasDatabase" },
		{ AtlasDirectoryEnums::DIR_CATALOGS, "AtlasCatalogs" },
		{ AtlasDirectoryEnums::DIR_PLUGINS, "AtlasPlugins" }
	};

	wxString getDatabasePath();
	wxString getDirectoryPath(AtlasDirectoryEnums directory);
	wxString mapDirectoryEnumToString(AtlasDirectoryEnums directory);
};

#endif