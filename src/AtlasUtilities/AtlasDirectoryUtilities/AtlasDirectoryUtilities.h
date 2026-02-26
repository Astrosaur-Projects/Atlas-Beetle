#ifndef ATLAS_DIRECTORY_UTILITIES_H
#define ATLAS_DIRECTORY_UTILITIES_H

#include <string>

namespace AtlasDirectoryUtilities
{
	enum class AtlasDirectoryEnums : int
	{
		DIR_CATALOGS,
		DIR_PLUGINS,
		DIR_DATABASE
	};

	std::string GetDatabasePath();

	std::string GetDirectoryPath(AtlasDirectoryEnums directory);

	std::string GetDirectoryName(AtlasDirectoryEnums directory);
};

#endif