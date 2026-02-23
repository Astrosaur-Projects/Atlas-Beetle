#include "AtlasApp/AtlasRenderLayers/AtlasRenderGrid/AtlasRenderGrid.h"
#include "AtlasApp/AtlasRenderLayers/AtlasRenderHorizon/AtlasRenderHorizon.h"
#include "AtlasApp/AtlasRenderLayers/AtlasRenderStars/AtlasRenderStars.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayerInterface.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderSky/AtlasRenderSky.h"
#include <GL/glew.h>
#include <memory>
#include <utility>

AtlasRenderSky::AtlasRenderSky()
{
	this->AddLayer(std::move(std::make_unique<AtlasRenderGrid>()));
	this->AddLayer(std::move(std::make_unique<AtlasRenderStars>()));
	this->AddLayer(std::move(std::make_unique<AtlasRenderHorizon>()));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void AtlasRenderSky::AddLayer(std::unique_ptr<AtlasRenderLayerInterface> layer)
{
	layer->Initialize();

	layers.push_back(std::move(layer));
}

void AtlasRenderSky::Render(const AtlasCamera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const std::unique_ptr<AtlasRenderLayerInterface>& layer : layers) {
		layer->Render(camera);
	}
}