#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateDatabase/AtlasCreateDatabase.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateTableCatalogDirectory/AtlasCreateTableCatalogDirectory.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateTableStarIndex/AtlasCreateTableStarIndex.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasCreateTableStarRenderData/AtlasCreateTableStarRenderData.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasOpenDatabase/AtlasOpenDatabase.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasResetTableCatalogDirectory/AtlasResetTableCatalogDirectory.h"
#include <expected>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateDatabase::initialize()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasOpenDatabase::open(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateTableCatalogDirectory::create(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::reset(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateTableStarIndex::create(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateTableStarRenderData::create(database); });

	sqlite3_close(database);

	return initDbResult;
}