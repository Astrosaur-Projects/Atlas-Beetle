#ifndef ATLAS_RENDER_SKY_H
#define ATLAS_RENDER_SKY_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayers/AtlasLayerInterface.h"
#include <memory>
#include <vector>

class AtlasRenderSky
{
public:
	AtlasRenderSky();

	void AddLayer(std::unique_ptr<AtlasLayerInterface> layer);
	void Render(const AtlasCamera& camera);

private:
	std::vector<std::unique_ptr<AtlasLayerInterface>> layers;
};

#endif