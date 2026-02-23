#include "AtlasApp/AtlasSetupLayers/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasApp/AtlasSetupLayers/AtlasResetCatalogDirectory/AtlasResetCatalogDirectory.h"
#include "AtlasApp/AtlasSetupLayers/AtlasSetupCurl/AtlasSetupCurl.h"
#include "AtlasApp/AtlasSetupLayers/AtlasSetupDatabase/AtlasSetupDatabase.h"
#include "AtlasApp/AtlasSetupLayers/AtlasSetupDefaultCatalog/AtlasSetupDefaultCatalog.h"
#include "AtlasApp/AtlasSetupLayers/AtlasSetupDirectory/AtlasSetupDirectory.h"
#include "AtlasCore/AtlasStartup/AtlasSetupApp/AtlasSetupApp.h"
#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <utility>

AtlasSetupApp::AtlasSetupApp()
{
	this->AddLayer(std::make_unique<AtlasSetupCurl>());
	this->AddLayer(std::make_unique<AtlasSetupDirectory>());
	this->AddLayer(std::make_unique<AtlasSetupDatabase>());
	this->AddLayer(std::make_unique<AtlasResetCatalogDirectory>());
	this->AddLayer(std::make_unique<AtlasDownloadCatalogs>());
	this->AddLayer(std::make_unique<AtlasSetupDefaultCatalog>());
}

void AtlasSetupApp::AddLayer(std::unique_ptr<AtlasSetupLayerInterface> layer)
{
	layers.push_back(std::move(layer));
}

std::expected<bool, std::string> AtlasSetupApp::Setup()
{
	std::expected<bool, std::string> setupResult = true;

	for (const std::unique_ptr<AtlasSetupLayerInterface>& layer : layers) {
		setupResult = setupResult.and_then([&](bool) { layer->Initialize(); return layer->Setup(); });
	}

	return setupResult;
}