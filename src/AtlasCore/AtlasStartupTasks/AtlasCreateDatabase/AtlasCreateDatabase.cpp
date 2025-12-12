#include "AtlasCreateCatalogDirectoryTable.h"
#include "AtlasCreateDatabase.h"
#include "AtlasOpenDatabase.h"
#include <expected>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateDatabase::initialize()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasOpenDatabase::open(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::create(database); });

	sqlite3_close(database);

	return initDbResult;
}