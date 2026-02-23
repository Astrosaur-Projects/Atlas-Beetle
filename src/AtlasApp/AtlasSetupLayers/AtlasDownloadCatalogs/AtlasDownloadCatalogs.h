#ifndef ATLAS_DOWNLOAD_CATALOGS_H
#define ATLAS_DOWNLOAD_CATALOGS_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <string>
#include <vector>

class AtlasDownloadCatalogs : public AtlasSetupLayerInterface
{
public:
	std::expected<bool, std::string> Setup() override;

private:
	std::expected<bool, std::string> DownloadCatalogs(std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs);
	std::expected<bool, std::string> DownloadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog);
};

#endif