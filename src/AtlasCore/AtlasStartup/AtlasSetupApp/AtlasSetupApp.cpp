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
	auto setupCurl = std::make_unique<AtlasSetupCurl>();
	auto setupDirectory = std::make_unique<AtlasSetupDirectory>();
	auto setupDatabase = std::make_unique<AtlasSetupDatabase>();
	auto resetCatalogDirectory = std::make_unique<AtlasResetCatalogDirectory>();
	auto downloadCatalogs = std::make_unique<AtlasDownloadCatalogs>();
	auto setupDefaultCatalog = std::make_unique<AtlasSetupDefaultCatalog>();

	this->AddLayer(std::move(setupCurl));
	this->AddLayer(std::move(setupDirectory));
	this->AddLayer(std::move(setupDatabase));
	this->AddLayer(std::move(resetCatalogDirectory));
	this->AddLayer(std::move(downloadCatalogs));
	this->AddLayer(std::move(setupDefaultCatalog));
}

void AtlasSetupApp::AddLayer(std::unique_ptr<AtlasSetupLayerInterface> layer)
{
	layer->Initialize();

	layers.push_back(std::move(layer));
}

std::expected<bool, std::string> AtlasSetupApp::Setup()
{
	std::expected<bool, std::string> applicationSetupResult = true;

	for (const std::unique_ptr<AtlasSetupLayerInterface>& layer : layers) {
		applicationSetupResult = applicationSetupResult.and_then([&](bool) { return layer->Setup(); });
	}

	return applicationSetupResult;
}