#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasGraphicsLayerInterface.h"
#include "AtlasCore/AtlasGraphics/AtlasGraphicsEngine/AtlasGraphicsEngine.h"
#include <GL/glew.h>
#include <memory>
#include <utility>

AtlasGraphicsEngine::AtlasGraphicsEngine()
{
}

void AtlasGraphicsEngine::Initialize()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (const std::unique_ptr<AtlasGraphicsLayerInterface>& layer : layers) {
		layer->Initialize();
	}
}

void AtlasGraphicsEngine::AddLayer(std::unique_ptr<AtlasGraphicsLayerInterface> layer)
{
	layers.push_back(std::move(layer));
}

void AtlasGraphicsEngine::Render(const AtlasCamera& camera)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (const std::unique_ptr<AtlasGraphicsLayerInterface>& layer : layers) {
		layer->Render(camera);
	}
}