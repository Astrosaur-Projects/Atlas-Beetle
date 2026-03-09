#ifndef ATLAS_GRAPHICS_CONFIG_REPOSITORY_H
#define ATLAS_GRAPHICS_CONFIG_REPOSITORY_H

#include "AtlasCore/AtlasConfig/AtlasGraphicsConfig/AtlasGraphicsConfig.h"
#include <expected>
#include <string>

class AtlasGraphicsConfigRepository
{
public:
	std::expected<bool, std::string> Load(AtlasGraphicsConfig& config);
	std::expected<bool, std::string> Save(const AtlasGraphicsConfig& config);
};

#endif