#include "AtlasApp/AtlasStartupLayers/AtlasDownloadCatalogs/AtlasDownloadCatalogs.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include "AtlasUtilities/AtlasDownloadUtilities/AtlasDownloadUtilities.h"
#include <curl/curl.h>
#include <expected>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <wx/filename.h>

void AtlasDownloadCatalogs::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());
}

std::expected<bool, std::string> AtlasDownloadCatalogs::Start()
{
	return AtlasDatabaseUtilities::prepareStatement(database.get(), SELECT_FROM_CATALOG_DIRECTORY)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::query<AtlasCatalogUtilities::CatalogRecord>(statement.get(), database.get(), AtlasCatalogUtilities::initializeCatalogRecordFromSQLStatement); })
		.and_then([&](std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs) { return DownloadCatalogs(catalogs); });
}

std::expected<bool, std::string> AtlasDownloadCatalogs::DownloadCatalogs(std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs)
{
	std::expected<bool, std::string> downloadCatalogsResult = true;

	for (const AtlasCatalogUtilities::CatalogRecord& catalog : catalogs) {
		downloadCatalogsResult = downloadCatalogsResult.and_then([&](bool) { return DownloadCatalog(catalog); });

		if (!downloadCatalogsResult.has_value()) { break; }
	}

	return downloadCatalogsResult;
}

std::expected<bool, std::string> AtlasDownloadCatalogs::DownloadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog)
{
	wxFileName fileName(catalog.path);

	if (fileName.FileExists()) { return true; }

	std::string querySourceUrl = catalog.source + "&-out.all" + "&-out.max=unlimited";

	return AtlasDownloadUtilities::download(querySourceUrl, catalog.path)
		.transform([](CURLcode code) { return code == SQLITE_OK; });
}