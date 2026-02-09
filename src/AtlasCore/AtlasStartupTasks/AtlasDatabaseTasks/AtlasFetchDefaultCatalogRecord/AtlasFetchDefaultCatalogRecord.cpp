#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDefaultCatalogRecord/AtlasFetchDefaultCatalogRecord.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>
#include <vector>

std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> AtlasFetchDefaultCatalogRecord::fetch(sqlite3* database)
{
	std::expected<sqlite3_stmt*, std::string> fetchCatalogsResult = nullptr;

	fetchCatalogsResult = fetchCatalogsResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasFetchDefaultCatalogRecord::prepareStatement(statement, database); });

	return fetchCatalogsResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> { return AtlasFetchDefaultCatalogRecord::executeStatement(statement, database); });
}

std::expected<sqlite3_stmt*, std::string> AtlasFetchDefaultCatalogRecord::prepareStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::string sql = "SELECT * FROM CatalogDirectory WHERE id = 1;";

	int resultCode = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, nullptr);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error preparing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<AtlasCatalogUtilities::CatalogRecord, std::string> AtlasFetchDefaultCatalogRecord::executeStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::vector<AtlasCatalogUtilities::CatalogRecord> catalogs;

	int resultCode = SQLITE_OK;

	AtlasCatalogUtilities::CatalogRecord catalog;

	while ((resultCode = sqlite3_step(statement)) == SQLITE_ROW) {
		catalog.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
		catalog.source = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
		catalog.path = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2)));
		catalog.type = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
		catalog.isEnabled = sqlite3_column_int(statement, 4);
		catalog.isInstalled = sqlite3_column_int(statement, 5);

		break;
	}

	sqlite3_finalize(statement);

	if (resultCode != SQLITE_DONE) {
		std::string errorMessage = std::format("Error fetching rows from CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return catalog;
}