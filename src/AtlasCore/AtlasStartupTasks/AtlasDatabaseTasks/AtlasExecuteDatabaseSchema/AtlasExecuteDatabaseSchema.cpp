#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasExecuteDatabaseSchema/AtlasExecuteDatabaseSchema.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDoesTableExist/AtlasFetchDoesTableExist.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasResetTableCatalogDirectory/AtlasResetTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <tuple>

std::expected<bool, std::string> AtlasExecuteDatabaseSchema::initialize()
{
	sqlite3* database = nullptr;

	std::expected<bool, std::string> executeDatabaseSchemaResult = true;

	executeDatabaseSchemaResult = executeDatabaseSchemaResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasDatabaseUtilities::open(&database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasExecuteDatabaseSchema::create(database, "CatalogDirectory", AtlasExecuteDatabaseSchema::CREATE_TABLE_CATALOG_DIRECTORY); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasExecuteDatabaseSchema::create(database, "StarRenderData", AtlasExecuteDatabaseSchema::CREATE_TABLE_STAR_RENDER_DATA); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasExecuteDatabaseSchema::create(database, "StarIndex", AtlasExecuteDatabaseSchema::CREATE_TABLE_STAR_INDEX); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::reset(database); });

	std::ignore = AtlasDatabaseUtilities::close(database);

	return executeDatabaseSchemaResult;
}

std::expected<bool, std::string> AtlasExecuteDatabaseSchema::create(sqlite3* database, std::string table, std::string query)
{
	std::expected<bool, std::string> createTableIfNotExistsResult = AtlasFetchDoesTableExist::fetch(database, table);

	if (!createTableIfNotExistsResult.has_value() || createTableIfNotExistsResult.value()) {
		return createTableIfNotExistsResult;
	}

	createTableIfNotExistsResult = createTableIfNotExistsResult
		.and_then([&](bool success) -> std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) -> std::expected<bool, std::string> { return AtlasDatabaseUtilities::execute(statement, database); });

	return createTableIfNotExistsResult;
}