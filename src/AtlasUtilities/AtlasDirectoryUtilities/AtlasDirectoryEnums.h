#ifndef ATLAS_DIRECTORY_ENUMS_H
#define ATLAS_DIRECTORY_ENUMS_H

#include <map>

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

	std::string getDirectoryString(AtlasDirectoryEnums directory);
};

#endif