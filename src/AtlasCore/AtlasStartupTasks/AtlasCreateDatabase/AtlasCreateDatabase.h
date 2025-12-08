#ifndef ATLAS_CREATE_DB_TASK_H
#define ATLAS_CREATE_DB_TASK_H

#include <expected>
#include <string>
#include <sqlite3.h>

namespace AtlasCreateDatabase
{
	std::expected<bool, std::string> initialize();
	std::expected<bool, std::string> initDatabase(sqlite3* &database);
	std::expected<bool, std::string> initCatalogDirectoryTable(sqlite3* database);
};

#endif