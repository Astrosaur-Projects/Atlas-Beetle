#include "AtlasApp/AtlasStartupLayers/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasApp/AtlasStartupLayers/AtlasResetCatalogDirectory/AtlasResetCatalogDirectory.h"
#include "AtlasApp/AtlasStartupLayers/AtlasSetupCurl/AtlasSetupCurl.h"
#include "AtlasApp/AtlasStartupLayers/AtlasSetupDatabase/AtlasSetupDatabase.h"
#include "AtlasApp/AtlasStartupLayers/AtlasSetupDefaultCatalog/AtlasSetupDefaultCatalog.h"
#include "AtlasApp/AtlasStartupLayers/AtlasSetupDirectory/AtlasSetupDirectory.h"
#include "AtlasCore/AtlasStartup/AtlasStartApp/AtlasStartApp.h"
#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <utility>

AtlasStartApp::AtlasStartApp()
{
	this->AddLayer(std::make_unique<AtlasSetupCurl>());
	this->AddLayer(std::make_unique<AtlasSetupDirectory>());
	this->AddLayer(std::make_unique<AtlasSetupDatabase>());
	this->AddLayer(std::make_unique<AtlasResetCatalogDirectory>());
	this->AddLayer(std::make_unique<AtlasDownloadCatalogs>());
	this->AddLayer(std::make_unique<AtlasSetupDefaultCatalog>());
}

void AtlasStartApp::AddLayer(std::unique_ptr<AtlasStartupLayerInterface> layer)
{
	layers.push_back(std::move(layer));
}

std::expected<bool, std::string> AtlasStartApp::Start()
{
	std::expected<bool, std::string> setupResult = true;

	for (const std::unique_ptr<AtlasStartupLayerInterface>& layer : layers) {
		setupResult = setupResult.and_then([&](bool) { layer->Initialize(); return layer->Start(); });
	}

	return setupResult;
}