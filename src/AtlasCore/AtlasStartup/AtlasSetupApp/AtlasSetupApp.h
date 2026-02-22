#ifndef ATLAS_SETUP_APP_H
#define ATLAS_SETUP_APP_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include <memory>
#include <vector>

class AtlasSetupApp
{
public:
	AtlasSetupApp();

	void AddLayer(std::unique_ptr<AtlasSetupLayerInterface> layer);
	void Setup();

private:
	std::vector<std::unique_ptr<AtlasSetupLayerInterface>> layers;
};

#endif