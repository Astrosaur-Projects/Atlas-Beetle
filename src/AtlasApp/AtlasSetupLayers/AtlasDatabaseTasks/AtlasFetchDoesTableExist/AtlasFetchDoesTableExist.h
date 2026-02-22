#ifndef ATLAS_FETCH_DOES_TABLE_EXIST_TASK_H
#define ATLAS_FETCH_DOES_TABLE_EXIST_TASK_H

#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasFetchDoesTableExist
{
	std::expected<bool, std::string> fetch(sqlite3* database, std::string table);
};

#endif