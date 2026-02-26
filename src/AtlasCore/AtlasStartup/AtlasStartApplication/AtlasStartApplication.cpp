#include "AtlasApp/AtlasStartupLayers/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasApp/AtlasStartupLayers/AtlasResetCatalogDirectory/AtlasResetCatalogDirectory.h"
#include "AtlasApp/AtlasStartupLayers/AtlasLoadCurl/AtlasLoadCurl.h"
#include "AtlasApp/AtlasStartupLayers/AtlasInitializeDatabaseSchema/AtlasInitializeDatabaseSchema.h"
#include "AtlasApp/AtlasStartupLayers/AtlasImportDefaultCatalog/AtlasImportDefaultCatalog.h"
#include "AtlasApp/AtlasStartupLayers/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.h"
#include "AtlasCore/AtlasStartup/AtlasStartApplication/AtlasStartApplication.h"
#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include <expected>
#include <memory>
#include <string>
#include <utility>

AtlasStartApplication::AtlasStartApplication()
{
	this->AddLayer(std::make_unique<AtlasLoadCurl>());
	this->AddLayer(std::make_unique<AtlasCreateApplicationDirectory>());
	this->AddLayer(std::make_unique<AtlasInitializeDatabaseSchema>());
	this->AddLayer(std::make_unique<AtlasResetCatalogDirectory>());
	this->AddLayer(std::make_unique<AtlasDownloadCatalogs>());
	this->AddLayer(std::make_unique<AtlasImportDefaultCatalog>());
}

void AtlasStartApplication::AddLayer(std::unique_ptr<AtlasStartupLayerInterface> layer)
{
	layers.push_back(std::move(layer));
}

std::expected<bool, std::string> AtlasStartApplication::Start()
{
	std::expected<bool, std::string> setupResult = true;

	for (const std::unique_ptr<AtlasStartupLayerInterface>& layer : layers) {
		setupResult = setupResult.and_then([&](bool) { layer->Initialize(); return layer->Start(); });
	}

	return setupResult;
}