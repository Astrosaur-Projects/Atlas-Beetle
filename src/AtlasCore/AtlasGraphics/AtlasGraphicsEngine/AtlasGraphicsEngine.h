#ifndef ATLAS_GRAPHICS_ENGINE_H
#define ATLAS_GRAPHICS_ENGINE_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasGraphicsLayerInterface.h"
#include <memory>
#include <vector>

class AtlasGraphicsEngine
{
public:
	AtlasGraphicsEngine();

	void Initialize();
	void AddLayer(std::unique_ptr<AtlasGraphicsLayerInterface> layer);
	void Render(const AtlasCamera& camera);

private:
	std::vector<std::unique_ptr<AtlasGraphicsLayerInterface>> layers;
};

#endif