#ifndef ATLAS_OPEN_DB_TASK_H
#define ATLAS_OPEN_DB_TASK_H

#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasOpenDatabase
{
	std::expected<bool, std::string> open(sqlite3*& database);
};

#endif