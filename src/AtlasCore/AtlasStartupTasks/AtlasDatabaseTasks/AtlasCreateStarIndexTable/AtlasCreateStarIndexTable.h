#ifndef ATLAS_CREATE_STAR_INDEX_DB_TASK_H
#define ATLAS_CREATE_STAR_INDEX_DB_TASK_H

#include <expected>
#include <string>
#include <sqlite3.h>

namespace AtlasCreateStarIndexTable
{
	std::expected<bool, std::string> create(sqlite3* database);
	std::expected<bool, std::string> initStarIndex(sqlite3* database);
};

#endif