#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateCatalogDirectoryTable/AtlasCreateCatalogDirectoryTable.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateDatabase/AtlasCreateDatabase.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateStarIndexTable/AtlasCreateStarIndexTable.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateStarRenderDataTable/AtlasCreateStarRenderDataTable.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasOpenDatabase/AtlasOpenDatabase.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasResetCatalogDirectoryTable/AtlasResetCatalogDirectoryTable.h"
#include <expected>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateDatabase::initialize()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasOpenDatabase::open(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::create(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetCatalogDirectoryTable::reset(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateStarIndexTable::create(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateStarRenderDataTable::create(database); });

	sqlite3_close(database);

	return initDbResult;
}