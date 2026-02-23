#include "AtlasApp/AtlasSetupLayers/AtlasSetupDatabase/AtlasSetupDatabase.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <stdexcept>
#include <string>

void AtlasSetupDatabase::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = openDatabaseResult.value().get();
}

std::expected<bool, std::string> AtlasSetupDatabase::Setup()
{
	std::expected<bool, std::string> setupDatabaseResult = true;

	setupDatabaseResult = setupDatabaseResult
		.and_then([&](bool) { return this->CreateTable("CatalogDirectory", this->CREATE_TABLE_CATALOG_DIRECTORY); })
		.and_then([&](bool) { return this->CreateTable("StarRenderData", this->CREATE_TABLE_STAR_RENDER_DATA); })
		.and_then([&](bool) { return this->CreateTable("StarIndex", this->CREATE_TABLE_STAR_INDEX); })
		.and_then([&](bool) { return this->ExecuteStatement(this->CREATE_TRIGGER_INSERT_STAR_INDEX); })
		.and_then([&](bool) { return this->ExecuteStatement(this->CREATE_TRIGGER_DELETE_STAR_INDEX); });

	return setupDatabaseResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::CreateTable(std::string table, std::string query)
{
	std::expected<bool, std::string> doesTableExistResult = this->DoesTableExist(table);

	if (!doesTableExistResult.has_value() || doesTableExistResult.value()) {
		return doesTableExistResult;
	}

	std::expected<bool, std::string> createResult = true;

	createResult = createResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

	return createResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::DoesTableExist(std::string table)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, this->FETCH_DOES_TABLE_EXIST);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statement = prepareStatementResult.value().get();

	const auto initializeIntFromSQLStatement = [](sqlite3_stmt* statement) -> int { return sqlite3_column_int(statement, 0); };

	std::expected<bool, std::string> doesTableExistResult = true;

	doesTableExistResult = doesTableExistResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::bindStatementParameters(statement, table); })
		.and_then([&](bool) { return AtlasDatabaseUtilities::query<int>(statement, database, initializeIntFromSQLStatement); })
		.transform([](std::vector<int> records) { return records.front() > 0; });

	return doesTableExistResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::ExecuteStatement(std::string query)
{
	std::expected<bool, std::string> executeResult = true;

	executeResult = executeResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

	return executeResult;
}