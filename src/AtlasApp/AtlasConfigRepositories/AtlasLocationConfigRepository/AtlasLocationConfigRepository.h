#ifndef ATLAS_LOCATION_CONFIG_REPOSITORY_H
#define ATLAS_LOCATION_CONFIG_REPOSITORY_H

#include "AtlasCore/AtlasConfig/AtlasLocationConfig/AtlasLocationConfig.h"
#include <expected>
#include <string>

class AtlasLocationConfigRepository
{
public:
	std::expected<bool, std::string> Load(AtlasLocationConfig& config);
	std::expected<bool, std::string> Save(const AtlasLocationConfig& config);
};

#endif
