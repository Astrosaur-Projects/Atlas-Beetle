#ifndef ATLAS_CREATE_APP_DIR_TASK_H
#define ATLAS_CREATE_APP_DIR_TASK_H

#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <string>

namespace AtlasCreateApplicationDirectory
{
	std::expected<bool, std::string> initialize();
	std::expected<bool, std::string> initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory);
};

#endif