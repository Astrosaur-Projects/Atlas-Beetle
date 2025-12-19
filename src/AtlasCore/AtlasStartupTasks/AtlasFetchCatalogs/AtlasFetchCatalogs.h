#ifndef ATLAS_FETCH_CATALOGS_TASK_H
#define ATLAS_FETCH_CATALOGS_TASK_H

#include <AtlasCatalogRecord.h>
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace AtlasFetchCatalogs
{
	std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> fetch(sqlite3* database);
	std::expected<sqlite3_stmt*, std::string> prepareStatement(sqlite3_stmt* statement, sqlite3* database);
	std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> executeStatement(sqlite3_stmt* statement, sqlite3* database);
};

#endif