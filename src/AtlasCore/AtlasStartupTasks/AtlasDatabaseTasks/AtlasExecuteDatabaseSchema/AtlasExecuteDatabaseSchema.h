#ifndef ATLAS_EXECUTE_DATABASE_SCHEMA_TASK_H
#define ATLAS_EXECUTE_DATABASE_SCHEMA_TASK_H

#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasExecuteDatabaseSchema
{
	std::expected<bool, std::string> initialize();

	std::expected<bool, std::string> create(sqlite3* database, std::string table, std::string query);

	const std::string CREATE_TABLE_CATALOG_DIRECTORY = R"(
		CREATE TABLE IF NOT EXISTS CatalogDirectory (
			id			INTEGER PRIMARY KEY,
			name        TEXT    NOT NULL,
			source      TEXT    NOT NULL,
			path		TEXT    NOT NULL,
			type        INTEGER NOT NULL DEFAULT 0,
			isEnabled   INTEGER NOT NULL DEFAULT 0,
			isInstalled INTEGER NOT NULL DEFAULT 0
		);
	)";

	const std::string CREATE_TABLE_STAR_RENDER_DATA = R"(
		CREATE TABLE IF NOT EXISTS StarRenderData (
			id					INTEGER	PRIMARY	KEY,
			ra_rad				REAL	NOT NULL,
			dec_rad				REAL	NOT NULL,
			pm_ra				REAL	NOT NULL,
			pm_dec				REAL	NOT NULL,
			mag					REAL	NOT NULL,
			color_index			REAL	NOT NULL	DEFAULT 0,
			object_type			INTEGER	NOT NULL	DEFAULT 0,
			angular_size		REAL	NOT NULL	DEFAULT 0,
			orientation_angle	REAL
		);
	)";

	const std::string CREATE_TABLE_STAR_INDEX = R"(
		CREATE VIRTUAL TABLE StarIndex USING rtree(
			id,
			minX, maxX,
			minY, maxY,
			minZ, maxZ
		);
	)";
};

#endif