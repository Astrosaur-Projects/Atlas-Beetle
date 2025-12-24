#include "AtlasCatalogRecord.h"
#include "AtlasDirectoryEnums.h"
#include "AtlasDirectoryUtilities.h"
#include "AtlasDownloadCatalogs.h"
#include "AtlasDownloadUtilities.h"
#include "AtlasFetchCatalogs.h"
#include "AtlasOpenDatabase.h"
#include <curl/curl.h>
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <wx/filename.h>
#include <wx/string.h>

std::expected<bool, std::string> AtlasDownloadCatalogs::download()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> downloadCatalogsResult = true;

	downloadCatalogsResult = downloadCatalogsResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasOpenDatabase::open(database); })
		.and_then([&](bool success) -> std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> { return AtlasFetchCatalogs::fetch(database); })
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
	wxString path = AtlasDirectoryUtilities::getDirectoryPath(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_CATALOGS)
		+ wxFileName::GetPathSeparator()
		+ AtlasDownloadUtilities::getFilenameFromSource(catalog.source);

	wxFileName fileName(path);

	if (fileName.FileExists()) { return true; }

	return AtlasDownloadUtilities::download(catalog.source, path.ToStdString())
		.transform([](CURLcode code) { return code == SQLITE_OK; });
}