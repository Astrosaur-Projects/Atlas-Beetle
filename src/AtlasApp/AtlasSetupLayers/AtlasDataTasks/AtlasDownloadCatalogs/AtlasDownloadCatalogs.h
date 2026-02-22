#ifndef ATLAS_DOWNLOAD_CATALOGS_TASK_H
#define ATLAS_DOWNLOAD_CATALOGS_TASK_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <string>
#include <vector>

namespace AtlasDownloadCatalogs
{
	std::expected<bool, std::string> download();

	std::expected<bool, std::string> downloadCatalogs(std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs);

	std::expected<bool, std::string> downloadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog);
};

#endif