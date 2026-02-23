#ifndef ATLAS_DOWNLOAD_CATALOGS_H
#define ATLAS_DOWNLOAD_CATALOGS_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <string>
#include <vector>

class AtlasDownloadCatalogs : public AtlasSetupLayerInterface
{
public:
	void Initialize() override;
	std::expected<bool, std::string> Setup() override;

private:
	std::expected<bool, std::string> DownloadCatalogs(std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs);
	std::expected<bool, std::string> DownloadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog);

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;

	const std::string SELECT_FROM_CATALOG_DIRECTORY = "SELECT id, name, source, path, type, isEnabled, isInstalled FROM CatalogDirectory;";
};

#endif