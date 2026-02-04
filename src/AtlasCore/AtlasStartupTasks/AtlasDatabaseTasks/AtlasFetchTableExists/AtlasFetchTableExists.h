#ifndef ATLAS_FETCH_TABLE_EXISTS_TASK_H
#define ATLAS_FETCH_TABLE_EXISTS_TASK_H

#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasFetchTableExists
{
	std::expected<bool, std::string> fetch(sqlite3* database, std::string table);
	std::expected<sqlite3_stmt*, std::string> prepareStatement(sqlite3_stmt* statement, sqlite3* database);
	std::expected<sqlite3_stmt*, std::string> bindParameter(sqlite3_stmt* statement, int index, std::string parameter);
	std::expected<bool, std::string> executeStatement(sqlite3_stmt* statement, sqlite3* database);
};

#endif