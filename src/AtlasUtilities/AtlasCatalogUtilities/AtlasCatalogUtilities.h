#ifndef ATLAS_CATALOG_UTILITIES_H
#define ATLAS_CATALOG_UTILITIES_H

#include <sqlite3.h>
#include <string>

namespace AtlasCatalogUtilities
{
	enum class AtlasCatalogEnums : int
	{
		CAT_BSC5P,
	};

	enum class AtlasCatalogTypeEnums : int
	{
		STAR,
	};

	struct AtlasCatalogObject
	{
		AtlasCatalogEnums id;

		AtlasCatalogTypeEnums type;

		std::string name;

		std::string source;
	};

	struct CatalogRecord
	{
		int id;

		std::string name;

		std::string source;

		std::string path;

		int type;

		bool isEnabled = false;

		bool isInstalled = false;
	};

	const auto initializeCatalogRecordFromSQLStatement = [](sqlite3_stmt* statement) -> CatalogRecord {
		return CatalogRecord {
			.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1))),
			.source = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 2))),
			.path = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3))),
			.type = sqlite3_column_int(statement, 4),
			.isEnabled = (bool)sqlite3_column_int(statement, 5),
			.isInstalled = (bool)sqlite3_column_int(statement, 6),
		};
	};

	AtlasCatalogObject getDefaultCatalogObject();

	std::string getCatalogFilePath(AtlasCatalogObject catalog);
};

#endif