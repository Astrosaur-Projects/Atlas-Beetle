#ifndef ATLAS_CREATE_CATALOG_DIRECTORY_DB_TASK_H
#define ATLAS_CREATE_CATALOG_DIRECTORY_DB_TASK_H

#include <expected>
#include <string>
#include <sqlite3.h>

namespace AtlasCreateCatalogDirectoryTable
{
	std::expected<bool, std::string> create(sqlite3* database);
	std::expected<bool, std::string> initCatalogDirectory(sqlite3* database);
};

#endif