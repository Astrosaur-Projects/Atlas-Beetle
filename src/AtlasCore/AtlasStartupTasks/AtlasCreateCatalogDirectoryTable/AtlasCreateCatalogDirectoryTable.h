#ifndef ATLAS_CREATE_CATALOG_DIRECTORY_DB_TASK_H
#define ATLAS_CREATE_CATALOG_DIRECTORY_DB_TASK_H

#include "AtlasCatalogEnums.h"
#include <expected>
#include <string>
#include <sqlite3.h>

namespace AtlasCreateCatalogDirectoryTable
{
	std::expected<bool, std::string> create(sqlite3* database);
	std::expected<bool, std::string> initCatalogDirectory(sqlite3* database);
	std::expected<bool, std::string> resetCatalogDirectory(sqlite3* database);
	std::expected<bool, std::string> insertCatalogRecord(sqlite3* database, AtlasCatalogUtilities::AtlasCatalogEnums catalog);
	std::expected<sqlite3_stmt*, std::string> prepareStatement(sqlite3_stmt* statement, sqlite3* database);
	std::expected<sqlite3_stmt*, std::string> bindParameter(sqlite3_stmt* statement, int index, std::string parameter);
	std::expected<sqlite3_stmt*, std::string> executeStatement(sqlite3_stmt* statement, sqlite3* database);
};

#endif