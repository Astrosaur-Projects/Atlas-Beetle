#include "AtlasCatalogEnums.h"
#include "AtlasCatalogTypeEnums.h"
#include "AtlasCreateCatalogDirectoryTable.h"
#include <expected>
#include <format>
#include <sqlite3.h>
#include <string>

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::create(sqlite3* database)
{
	std::expected<bool, std::string> initDbResult = true;

	initDbResult = initDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::initCatalogDirectory(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::resetCatalogDirectory(database); });

	return initDbResult;
}

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::initCatalogDirectory(sqlite3* database)
{
	std::string sql = R"(
        CREATE TABLE IF NOT EXISTS CatalogDirectory (
            name        TEXT    NOT NULL,
            source      TEXT    NOT NULL,
			path		TEXT    NOT NULL,
            type        TEXT    NOT NULL,
            isEnabled   INTEGER NOT NULL DEFAULT 0,
            isInstalled INTEGER NOT NULL DEFAULT 0
        );
    )";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error creating CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::resetCatalogDirectory(sqlite3* database)
{
	std::expected<bool, std::string> resetDbResult = true;

	resetDbResult = resetDbResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::truncateCatalogDirectory(database); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::insertCatalogRecord(database, AtlasCatalogUtilities::AtlasCatalogEnums::CAT_SAO); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateCatalogDirectoryTable::insertCatalogRecord(database, AtlasCatalogUtilities::AtlasCatalogEnums::CAT_BSC5P); });

	return resetDbResult;
}

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::truncateCatalogDirectory(sqlite3* database)
{
	std::string sql = "DELETE FROM CatalogDirectory;";

	int resultCode = sqlite3_exec(database, sql.c_str(), nullptr, 0, nullptr);

	if (resultCode) {
		std::string errorMessage = std::format("Error truncating CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}

std::expected<bool, std::string> AtlasCreateCatalogDirectoryTable::insertCatalogRecord(sqlite3* database, AtlasCatalogUtilities::AtlasCatalogEnums catalog)
{
	std::expected<sqlite3_stmt*, std::string> insertRecordResult = nullptr;

	std::string filePath = "";

	insertRecordResult = insertRecordResult
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasCreateCatalogDirectoryTable::prepareStatement(statement, database); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasCreateCatalogDirectoryTable::bindParameter(statement, 1, AtlasCatalogUtilities::getCatalogName(catalog)); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasCreateCatalogDirectoryTable::bindParameter(statement, 2, AtlasCatalogUtilities::getCatalogSource(catalog)); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasCreateCatalogDirectoryTable::bindParameter(statement, 3, filePath); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasCreateCatalogDirectoryTable::bindParameter(statement, 4, AtlasCatalogUtilities::getCatalogTypeString(AtlasCatalogUtilities::getCatalogType(catalog))); })
		.and_then([&](sqlite3_stmt* statement) -> std::expected<sqlite3_stmt*, std::string> { return AtlasCreateCatalogDirectoryTable::executeStatement(statement, database); });

	return insertRecordResult
		.transform([](sqlite3_stmt* statement) { return sqlite3_finalize(statement) == SQLITE_OK; });
}

std::expected<sqlite3_stmt*, std::string> AtlasCreateCatalogDirectoryTable::prepareStatement(sqlite3_stmt* statement, sqlite3* database)
{
	std::string sql = R"(
        INSERT INTO CatalogDirectory (name, source, path, type)
        VALUES (?, ?, ?, ?);
    )";

	int resultCode = sqlite3_prepare_v2(database, sql.c_str(), -1, &statement, nullptr);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error preparing statement: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<sqlite3_stmt*, std::string> AtlasCreateCatalogDirectoryTable::bindParameter(sqlite3_stmt* statement, int index, std::string parameter)
{
	int resultCode = sqlite3_bind_text(statement, index, parameter.c_str(), -1, SQLITE_TRANSIENT);

	if (resultCode) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error binding parameter to statement: {} (Code: {})", parameter, resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}

std::expected<sqlite3_stmt*, std::string> AtlasCreateCatalogDirectoryTable::executeStatement(sqlite3_stmt* statement, sqlite3* database)
{
	int resultCode = sqlite3_step(statement);

	if (resultCode != SQLITE_DONE) {
		sqlite3_finalize(statement);

		std::string errorMessage = std::format("Error inserting row into CatalogDirectory: {} (Code: {})", sqlite3_errmsg(database), resultCode);

		return std::unexpected<std::string>(errorMessage);
	}

	return statement;
}