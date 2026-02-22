#include "AtlasApp/AtlasSetupLayers/AtlasDatabaseTasks/AtlasFetchDoesTableExist/AtlasFetchDoesTableExist.h"
#include "AtlasApp/AtlasSetupLayers/AtlasSetupDatabase/AtlasSetupDatabase.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <stdexcept>
#include <string>

void AtlasSetupDatabase::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDbResult = AtlasDatabaseUtilities::open();

	if (!openDbResult.has_value()) {
		throw std::runtime_error(openDbResult.error());
	}

	database = openDbResult.value().get();
}

std::expected<bool, std::string> AtlasSetupDatabase::Setup()
{
	std::expected<bool, std::string> setupDatabaseResult = true;

	setupDatabaseResult = setupDatabaseResult
		.and_then([&](bool) { return this->Create("CatalogDirectory", this->CREATE_TABLE_CATALOG_DIRECTORY); })
		.and_then([&](bool) { return this->Create("StarRenderData", this->CREATE_TABLE_STAR_RENDER_DATA); })
		.and_then([&](bool) { return this->Create("StarIndex", this->CREATE_TABLE_STAR_INDEX); })
		.and_then([&](bool) { return this->Execute(this->CREATE_TRIGGER_INSERT_STAR_INDEX); })
		.and_then([&](bool) { return this->Execute(this->CREATE_TRIGGER_DELETE_STAR_INDEX); });

	return setupDatabaseResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::Create(std::string table, std::string query)
{
	std::expected<bool, std::string> createTableIfNotExistsResult = AtlasFetchDoesTableExist::fetch(database, table);

	if (!createTableIfNotExistsResult.has_value() || createTableIfNotExistsResult.value()) {
		return createTableIfNotExistsResult;
	}

	std::expected<bool, std::string> createResult = true;

	createResult = createResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

	return createResult;
}

std::expected<bool, std::string> AtlasSetupDatabase::Execute(std::string query)
{
	std::expected<bool, std::string> executeResult = true;

	executeResult = executeResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::prepareStatement(database, query); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });

	return executeResult;
}