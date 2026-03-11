#ifndef ATLAS_RENDER_SKY_H
#define ATLAS_RENDER_SKY_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayerInterface.h"
#include <memory>
#include <vector>

class AtlasRenderSky
{
public:
	AtlasRenderSky();

	void Initialize();
	void AddLayer(std::unique_ptr<AtlasRenderLayerInterface> layer);
	void Render(const AtlasCamera& camera);

private:
	std::vector<std::unique_ptr<AtlasRenderLayerInterface>> layers;
};

#endif