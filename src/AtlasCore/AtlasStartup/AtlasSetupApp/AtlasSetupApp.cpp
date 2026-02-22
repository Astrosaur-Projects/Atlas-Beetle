#include "AtlasCore/AtlasStartup/AtlasSetupApp/AtlasSetupApp.h"
#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <utility>

AtlasSetupApp::AtlasSetupApp() { }

void AtlasSetupApp::AddLayer(std::unique_ptr<AtlasSetupLayerInterface> layer)
{
	layer->Initialize();

	layers.push_back(std::move(layer));
}

void AtlasSetupApp::Setup()
{
	std::expected<bool, std::string> applicationSetupResult = true;

	for (const std::unique_ptr<AtlasSetupLayerInterface>& layer : layers) {
		applicationSetupResult = applicationSetupResult.and_then([&](bool) { return layer->Setup(); });
	}
}