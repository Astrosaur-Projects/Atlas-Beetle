#include "AtlasCore/AtlasStartup/AtlasStartApplication/AtlasStartApplication.h"
#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <utility>

AtlasStartApplication::AtlasStartApplication()
{
}

void AtlasStartApplication::AddLayer(std::unique_ptr<AtlasStartupLayerInterface> layer)
{
	layers.push_back(std::move(layer));
}

std::expected<bool, std::string> AtlasStartApplication::Start()
{
	std::expected<bool, std::string> startApplicationResult = true;

	for (const std::unique_ptr<AtlasStartupLayerInterface>& layer : layers) {
		startApplicationResult = startApplicationResult.and_then([&](bool) { layer->Initialize(); return layer->Start(); });
	}

	return startApplicationResult;
}