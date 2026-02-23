#ifndef ATLAS_SETUP_APP_H
#define ATLAS_SETUP_APP_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <vector>

class AtlasStartApp
{
public:
	AtlasStartApp();

	void AddLayer(std::unique_ptr<AtlasStartupLayerInterface> layer);
	std::expected<bool, std::string> Start();

private:
	std::vector<std::unique_ptr<AtlasStartupLayerInterface>> layers;
};

#endif