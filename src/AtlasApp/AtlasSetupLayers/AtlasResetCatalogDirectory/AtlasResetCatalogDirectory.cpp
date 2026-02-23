#include "AtlasApp/AtlasSetupLayers/AtlasResetCatalogDirectory/AtlasResetCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

void AtlasResetCatalogDirectory::Initialize()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = openDatabaseResult.value().get();
}

std::expected<bool, std::string> AtlasResetCatalogDirectory::Setup()
{
	std::expected<bool, std::string> resetCatalogDirectoryResult = true;

	resetCatalogDirectoryResult = resetCatalogDirectoryResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetCatalogDirectory::TruncateCatalogDirectory(); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetCatalogDirectory::InsertDefaultCatalogRecord(); });

	return resetCatalogDirectoryResult;
}

std::expected<bool, std::string> AtlasResetCatalogDirectory::TruncateCatalogDirectory()
{
	const std::string TRUNCATE_CATALOG_DIRECTORY = "DELETE FROM CatalogDirectory;";

	return AtlasDatabaseUtilities::prepareStatement(database, TRUNCATE_CATALOG_DIRECTORY)
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) { return AtlasDatabaseUtilities::execute(statement.get(), database); });
}

std::expected<bool, std::string> AtlasResetCatalogDirectory::InsertDefaultCatalogRecord()
{
	const std::string INSERT_INTO_CATALOG_DIRECTORY = R"(
        INSERT INTO CatalogDirectory (id, name, source, path)
        VALUES (?, ?, ?, ?);
    )";

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, INSERT_INTO_CATALOG_DIRECTORY);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	sqlite3_stmt* statment = prepareStatementResult.value().get();

	AtlasCatalogUtilities::AtlasCatalogObject catalog = AtlasCatalogUtilities::getDefaultCatalogObject();

	std::expected<bool, std::string> insertDefaultCatalogRecordResult = true;

	insertDefaultCatalogRecordResult = insertDefaultCatalogRecordResult
		.and_then([&](bool) { return AtlasDatabaseUtilities::bindStatementParameters(statment, 0, catalog.name, catalog.source, AtlasCatalogUtilities::getCatalogFilePath(catalog)); })
		.and_then([&](bool) { return AtlasDatabaseUtilities::execute(statment, database); });

	return insertDefaultCatalogRecordResult;
}