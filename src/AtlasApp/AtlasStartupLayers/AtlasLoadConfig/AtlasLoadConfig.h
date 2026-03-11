#ifndef ATLAS_LOAD_CONFIG_H
#define ATLAS_LOAD_CONFIG_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include <expected>
#include <string>

class AtlasLoadConfig : public AtlasStartupLayerInterface
{
public:
	std::expected<bool, std::string> Start() override;
};

#endif
