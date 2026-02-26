#ifndef ATLAS_START_APPLICATION_H
#define ATLAS_START_APPLICATION_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <vector>

class AtlasStartApplication
{
public:
	AtlasStartApplication();

	void AddLayer(std::unique_ptr<AtlasStartupLayerInterface> layer);
	std::expected<bool, std::string> Start();

private:
	std::vector<std::unique_ptr<AtlasStartupLayerInterface>> layers;
};

#endif