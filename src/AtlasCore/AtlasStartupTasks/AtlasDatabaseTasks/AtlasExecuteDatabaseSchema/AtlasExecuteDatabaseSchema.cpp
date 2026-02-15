#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasExecuteDatabaseSchema/AtlasExecuteDatabaseSchema.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasFetchDoesTableExist/AtlasFetchDoesTableExist.h"
#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasResetTableCatalogDirectory/AtlasResetTableCatalogDirectory.h"
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
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasExecuteDatabaseSchema::create(database, "CatalogDirectory", AtlasExecuteDatabaseSchema::CREATE_TABLE_CATALOG_DIRECTORY); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasExecuteDatabaseSchema::create(database, "StarRenderData", AtlasExecuteDatabaseSchema::CREATE_TABLE_STAR_RENDER_DATA); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasExecuteDatabaseSchema::create(database, "StarIndex", AtlasExecuteDatabaseSchema::CREATE_TABLE_STAR_INDEX); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::reset(database); });

	return executeDatabaseSchemaResult;
}

std::expected<bool, std::string> AtlasExecuteDatabaseSchema::create(sqlite3* database, std::string table, std::string query)
{
	std::expected<bool, std::string> createTableIfNotExistsResult = AtlasFetchDoesTableExist::fetch(database, table);

	if (!createTableIfNotExistsResult.has_value() || createTableIfNotExistsResult.value()) {
		return createTableIfNotExistsResult;
	}

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, query);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statement = prepareStatementResult.value().get();

	return AtlasDatabaseUtilities::execute(statement, database);
}