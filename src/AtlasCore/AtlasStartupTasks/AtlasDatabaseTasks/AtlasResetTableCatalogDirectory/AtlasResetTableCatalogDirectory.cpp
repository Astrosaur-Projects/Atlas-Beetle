#include "AtlasCore/AtlasStartupTasks/AtlasDatabaseTasks/AtlasResetTableCatalogDirectory/AtlasResetTableCatalogDirectory.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasResetTableCatalogDirectory::reset(sqlite3* database)
{
	std::expected<bool, std::string> resetDbResult = true;

	resetDbResult = resetDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::truncateCatalogDirectory(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasResetTableCatalogDirectory::insertDefaultCatalogRecord(database); });

	return resetDbResult;
}

std::expected<bool, std::string> AtlasResetTableCatalogDirectory::truncateCatalogDirectory(sqlite3* database)
{
	std::string sql = "DELETE FROM CatalogDirectory;";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error truncating CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}

std::expected<bool, std::string> AtlasResetTableCatalogDirectory::insertDefaultCatalogRecord(sqlite3* database)
{
	AtlasCatalogUtilities::AtlasCatalogObject catalog = AtlasCatalogUtilities::getDefaultCatalogObject();

	std::expected<sqlite3_stmt*, std::string> insertRecordResult = nullptr;

	insertRecordResult = insertRecordResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasResetTableCatalogDirectory::prepareStatement(statement, database); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasResetTableCatalogDirectory::bindParameter(statement, 1, catalog.name); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasResetTableCatalogDirectory::bindParameter(statement, 2, catalog.source); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasResetTableCatalogDirectory::bindParameter(statement, 3, AtlasCatalogUtilities::getCatalogFilePath(catalog)); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasResetTableCatalogDirectory::executeStatement(statement, database); });

	return insertRecordResult
		.transform([](sqlite3_stmt* statement) { return sqlite3_finalize(statement) == SQLITE_OK; });
}

std::expected<sqlite3_stmt*, std::string> AtlasResetTableCatalogDirectory::prepareStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::string sql = R"(
        INSERT INTO CatalogDirectory (name, source, path)
        VALUES (?, ?, ?);
    )";

	int resultCode = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, nullptr);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error preparing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<sqlite3_stmt*, std::string> AtlasResetTableCatalogDirectory::bindParameter(sqlite3_stmt* statement, int index, std::string parameter)
{
	int resultCode = sqlite3_bind_text(statement, index, parameter.c_str(), -1, SQLITE_TRANSIENT);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error binding parameter to statement: {} (Code: {})", parameter, resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<sqlite3_stmt*, std::string> AtlasResetTableCatalogDirectory::executeStatement(sqlite3_stmt* statement, sqlite3* database)
{
	int resultCode = sqlite3_step(statement);

	if (resultCode != SQLITE_DONE) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error inserting row into CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}