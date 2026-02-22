#ifndef ATLAS_RESET_CATALOG_DIRECTORY_TASK_H
#define ATLAS_RESET_CATALOG_DIRECTORY_TASK_H

#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasResetTableCatalogDirectory
{
	std::expected<bool, std::string> reset(sqlite3* database);

	std::expected<bool, std::string> truncateCatalogDirectory(sqlite3* database);

	std::expected<bool, std::string> insertDefaultCatalogRecord(sqlite3* database);
};

#endif