#ifndef ATLAS_OPEN_DB_TASK_H
#define ATLAS_OPEN_DB_TASK_H

#include <expected>
#include <string>
#include <sqlite3.h>

namespace AtlasOpenDatabase
{
	std::expected<bool, std::string> open(sqlite3*& database);
};

#endif