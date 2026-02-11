#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasResetTableCatalogDirectory/AtlasResetTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasResetTableCatalogDirectory::reset(sqlite3* database)
{
	std::expected<bool, std::string> resetCatalogDirectoryResult = true;

	resetCatalogDirectoryResult = resetCatalogDirectoryResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::truncateCatalogDirectory(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::insertDefaultCatalogRecord(database); });

	return resetCatalogDirectoryResult;
}

std::expected<bool, std::string> AtlasResetTableCatalogDirectory::truncateCatalogDirectory(sqlite3* database)
{
	const std::string TRUNCATE_CATALOG_DIRECTORY = "DELETE FROM CatalogDirectory;";

	std::expected<bool, std::string> truncateCatalogDirectoryResult = true;

	truncateCatalogDirectoryResult = truncateCatalogDirectoryResult
		.and_then([&](bool success) -> std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> { return AtlasDatabaseUtilities::prepareStatement(database, TRUNCATE_CATALOG_DIRECTORY); })
		.and_then([&](AtlasDatabaseUtilities::MemorySafeStatement statement) -> std::expected<bool, std::string> { return AtlasDatabaseUtilities::execute(statement, database); });

	return truncateCatalogDirectoryResult;
}

std::expected<bool, std::string> AtlasResetTableCatalogDirectory::insertDefaultCatalogRecord(sqlite3* database)
{
	const std::string INSERT_INTO_CATALOG_DIRECTORY = R"(
        INSERT INTO CatalogDirectory (id, name, source, path)
        VALUES (?, ?, ?, ?);
    )";

	AtlasCatalogUtilities::AtlasCatalogObject catalog = AtlasCatalogUtilities::getDefaultCatalogObject();

	std::expected<bool, std::string> insertDefaultCatalogRecordResult = true;

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database, INSERT_INTO_CATALOG_DIRECTORY);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	insertDefaultCatalogRecordResult = insertDefaultCatalogRecordResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasDatabaseUtilities::bindStatementParameters(prepareStatementResult.value(), 0, catalog.name, catalog.source, AtlasCatalogUtilities::getCatalogFilePath(catalog)); })
		.and_then([&](bool success) -> std::expected<int, std::string> { return AtlasDatabaseUtilities::execute(prepareStatementResult.value(), database); });

	return insertDefaultCatalogRecordResult;
}