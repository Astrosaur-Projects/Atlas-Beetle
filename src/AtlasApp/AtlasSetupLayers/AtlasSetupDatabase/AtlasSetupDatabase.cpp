#include "AtlasApp/AtlasSetupLayers/AtlasSetupDatabase/AtlasSetupDatabase.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

void AtlasSetupDatabase::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());
}

std::expected<bool, std::string> AtlasSetupDatabase::Setup()
{
	std::expected<bool, std::string> setupDatabaseResult = true;

	setupDatabaseResult = setupDatabaseResult
		.and_then([&](bool) { return CreateTable("CatalogDirectory", CREATE_TABLE_CATALOG_DIRECTORY); })
		.and_then([&](bool) { return CreateTable("StarRenderData", CREATE_TABLE_STAR_RENDER_DATA); })
		.and_then([&](bool) { return CreateTable("StarIndex", CREATE_TABLE_STAR_INDEX); })
		.and_then([&](bool) { return ExecuteStatement(CREATE_TRIGGER_INSERT_STAR_INDEX); })
		.and_then([&](bool) { return ExecuteStatement(CREATE_TRIGGER_DELETE_STAR_INDEX); });

	return setupDatabaseResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::CreateTable(std::string table, std::string query)
{
	std::expected<bool, std::string> doesTableExistResult = DoesTableExist(table);

	if (!doesTableExistResult.has_value() || doesTableExistResult.value()) {
		return doesTableExistResult;
	}

	std::expected<bool, std::string> createResult = true;

	createResult = createResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database.get(), query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database.get()); });

	return createResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::DoesTableExist(std::string table)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database.get(), FETCH_DOES_TABLE_EXIST);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statement = prepareStatementResult.value().get();

	const auto initializeIntFromSQLStatement = [](sqlite3_stmt* statement) -> int { return sqlite3_column_int(statement, 0); };

	std::expected<bool, std::string> doesTableExistResult = true;

	doesTableExistResult = doesTableExistResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::bindStatementParameters(statement, table); })
		.and_then([&](bool) { return AtlasDatabaseUtilities::query<int>(statement, database.get(), initializeIntFromSQLStatement); })
		.transform([](std::vector<int> records) { return records.front() > 0; });

	return doesTableExistResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::ExecuteStatement(std::string query)
{
	std::expected<bool, std::string> executeResult = true;

	executeResult = executeResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database.get(), query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database.get()); });

	return executeResult;
}