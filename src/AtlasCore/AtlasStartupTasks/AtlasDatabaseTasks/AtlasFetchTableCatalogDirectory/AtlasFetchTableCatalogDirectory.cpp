#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogRecord.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchTableCatalogDirectory/AtlasFetchTableCatalogDirectory.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> AtlasFetchTableCatalogDirectory::fetch(sqlite3* database)
{
	std::expected<sqlite3_stmt*, std::string> fetchCatalogsResult = nullptr;

	fetchCatalogsResult = fetchCatalogsResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasFetchTableCatalogDirectory::prepareStatement(statement, database); });

	return fetchCatalogsResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> { return AtlasFetchTableCatalogDirectory::executeStatement(statement, database); });
}

std::expected<sqlite3_stmt*, std::string> AtlasFetchTableCatalogDirectory::prepareStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::string sql = "SELECT * FROM CatalogDirectory;";

	int resultCode = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, nullptr);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error preparing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> AtlasFetchTableCatalogDirectory::executeStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs;

	int resultCode = SQLITE_OK;

	while ((resultCode = sqlite3_step(statement)) == SQLITE_ROW) {
		AtlasCatalogUtilities::CatalogRecord catalog;

		catalog.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
		catalog.source = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
		catalog.path = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
		catalog.type = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
		catalog.isEnabled = sqlite3_column_int(statement, 4);
		catalog.isInstalled = sqlite3_column_int(statement, 5);

		catalogs.push_back(catalog);
	}

	sqlite3_finalize(statement);

	if (resultCode != SQLITE_DONE) {
		std::string errorMessage = std::format("Error fetching rows from CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return catalogs;
}