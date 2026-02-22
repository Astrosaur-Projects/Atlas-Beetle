#include "AtlasApp/AtlasSetupLayers/AtlasDataTasks/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasFetchTableCatalogDirectory/AtlasFetchTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include "AtlasUtilities/AtlasDownloadUtilities/AtlasDownloadUtilities.h"
#include <curl/curl.h>
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <wx/filename.h>

std::expected<bool, std::string> AtlasDownloadCatalogs::download()
{
	return AtlasDatabaseUtilities::open()
		.and_then([](AtlasDatabaseUtilities::MemorySafeDatabase database) { return AtlasFetchTableCatalogDirectory::fetch(database.get()); })
		.and_then([](std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs) { return AtlasDownloadCatalogs::downloadCatalogs(catalogs); });
}

std::expected<bool, std::string> AtlasDownloadCatalogs::downloadCatalogs(std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs)
{
	std::expected<bool, std::string> downloadCatalogsResult = true;

	for (const AtlasCatalogUtilities::CatalogRecord& catalog : catalogs) {
		downloadCatalogsResult = downloadCatalogsResult
			.and_then([&](bool) { return AtlasDownloadCatalogs::downloadCatalog(catalog); });

		if (!downloadCatalogsResult.has_value()) { break; }
	}

	return downloadCatalogsResult;
}

std::expected<bool, std::string> AtlasDownloadCatalogs::downloadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog)
{
	wxFileName fileName(catalog.path);

	if (fileName.FileExists()) { return true; }

	std::string querySourceUrl = catalog.source + "&-out.all" + "&-out.max=unlimited";

	std::expected<bool, std::string> downloadCatalogResult = true;

	return AtlasDownloadUtilities::download(querySourceUrl, catalog.path)
		.transform([](CURLcode code) { return code == SQLITE_OK; });
}