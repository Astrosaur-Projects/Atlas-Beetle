#include "AtlasCore/AtlasStartupTasks/AtlasDataTasks/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchTableCatalogDirectory/AtlasFetchTableCatalogDirectory.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasOpenDatabase/AtlasOpenDatabase.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDownloadUtilities/AtlasDownloadUtilities.h"
#include <curl/curl.h>
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <wx/filename.h>

std::expected<bool, std::string> AtlasDownloadCatalogs::download()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> downloadCatalogsResult = true;

	downloadCatalogsResult = downloadCatalogsResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasOpenDatabase::open(database); })
		.and_then([&](bool success) -> std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> { return AtlasFetchTableCatalogDirectory::fetch(database); })
		.and_then([&](std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs) -> std::expected<bool, std::string> { return AtlasDownloadCatalogs::downloadCatalogs(catalogs); });

	sqlite3_close(database);

	return downloadCatalogsResult;
}

std::expected<bool, std::string> AtlasDownloadCatalogs::downloadCatalogs(std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs)
{
	std::expected<bool, std::string> downloadCatalogsResult = true;

	for (const AtlasCatalogUtilities::CatalogRecord& catalog : catalogs) {
		downloadCatalogsResult = downloadCatalogsResult.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasDownloadCatalogs::downloadCatalog(catalog); });
		if (!downloadCatalogsResult.has_value()) { break; }
	}

	return downloadCatalogsResult;
}

std::expected<bool, std::string> AtlasDownloadCatalogs::downloadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog)
{
	wxFileName fileName(catalog.path);

	if (fileName.FileExists()) { return true; }

	std::string querySourceUrl = catalog.source + "&-out.all" + "&-out.max=unlimited";

	return AtlasDownloadUtilities::download(querySourceUrl, catalog.path)
		.transform([](CURLcode code) { return code == SQLITE_OK; });
}