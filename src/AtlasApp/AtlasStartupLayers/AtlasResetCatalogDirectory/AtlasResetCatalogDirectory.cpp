#include "AtlasApp/AtlasStartupLayers/AtlasResetCatalogDirectory/AtlasResetCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>

void AtlasResetCatalogDirectory::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::Open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());
}

std::expected<bool, std::string> AtlasResetCatalogDirectory::Start()
{
	std::expected<bool, std::string> resetCatalogDirectoryResult = true;

	resetCatalogDirectoryResult = resetCatalogDirectoryResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetCatalogDirectory::TruncateCatalogDirectory(); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetCatalogDirectory::InsertDefaultCatalogRecord(); });

	return resetCatalogDirectoryResult;
}

std::expected<bool, std::string> AtlasResetCatalogDirectory::TruncateCatalogDirectory()
{
	return AtlasDatabaseUtilities::PrepareStatement(database.get(), TRUNCATE_CATALOG_DIRECTORY)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::Execute(statement.get(), database.get()); });
}

std::expected<bool, std::string> AtlasResetCatalogDirectory::InsertDefaultCatalogRecord()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), INSERT_INTO_CATALOG_DIRECTORY);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statment = prepareStatementResult.value().get();

	AtlasCatalogUtilities::AtlasCatalogObject catalog = AtlasCatalogUtilities::GetDefaultCatalogObject();

	std::expected<bool, std::string> insertDefaultCatalogRecordResult = true;

	insertDefaultCatalogRecordResult = insertDefaultCatalogRecordResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::BindStatementParameters(statment, 0, catalog.name, catalog.source, AtlasCatalogUtilities::GetCatalogFilePath(catalog)); })
		.and_then([&](bool) { return AtlasDatabaseUtilities::Execute(statment, database.get()); });

	return insertDefaultCatalogRecordResult;
}