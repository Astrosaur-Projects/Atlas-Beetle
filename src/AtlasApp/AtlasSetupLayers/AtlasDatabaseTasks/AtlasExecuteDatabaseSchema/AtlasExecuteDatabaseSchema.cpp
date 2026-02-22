#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasExecuteDatabaseSchema/AtlasExecuteDatabaseSchema.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasFetchDoesTableExist/AtlasFetchDoesTableExist.h"
#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasResetTableCatalogDirectory/AtlasResetTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasExecuteDatabaseSchema::initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		return std::unexpected<std::string>(openDatabaseResult.error());
	}

	sqlite3* database = openDatabaseResult.value().get();

	std::expected<bool, std::string> executeDatabaseSchemaResult = true;

	executeDatabaseSchemaResult = executeDatabaseSchemaResult
		.and_then([&](bool) { return AtlasExecuteDatabaseSchema::create(database, "CatalogDirectory", AtlasExecuteDatabaseSchema::CREATE_TABLE_CATALOG_DIRECTORY); })
		.and_then([&](bool) { return AtlasExecuteDatabaseSchema::create(database, "StarRenderData", AtlasExecuteDatabaseSchema::CREATE_TABLE_STAR_RENDER_DATA); })
		.and_then([&](bool) { return AtlasExecuteDatabaseSchema::create(database, "StarIndex", AtlasExecuteDatabaseSchema::CREATE_TABLE_STAR_INDEX); })
		.and_then([&](bool) { return AtlasExecuteDatabaseSchema::execute(database, AtlasExecuteDatabaseSchema::CREATE_TRIGGER_INSERT_STAR_INDEX); })
		.and_then([&](bool) { return AtlasExecuteDatabaseSchema::execute(database, AtlasExecuteDatabaseSchema::CREATE_TRIGGER_DELETE_STAR_INDEX); })
		.and_then([&](bool) { return AtlasResetTableCatalogDirectory::reset(database); });

	return executeDatabaseSchemaResult;
}

std::expected<bool, std::string> AtlasExecuteDatabaseSchema::create(sqlite3* database, std::string table, std::string query)
{
	std::expected<bool, std::string> createTableIfNotExistsResult = AtlasFetchDoesTableExist::fetch(database, table);

	if (!createTableIfNotExistsResult.has_value() || createTableIfNotExistsResult.value()) {
		return createTableIfNotExistsResult;
	}

	std::expected<bool, std::string> createTableResult = true;

	createTableResult = createTableResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

	return createTableResult;
}

std::expected<bool, std::string> AtlasExecuteDatabaseSchema::execute(sqlite3* database, std::string query)
{
	std::expected<bool, std::string> executeQueryResult = true;

	executeQueryResult = executeQueryResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

	return executeQueryResult;
}

