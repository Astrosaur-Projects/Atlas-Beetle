#ifndef ATLAS_INITIALIZE_DATABASE_SCHEMA_H
#define ATLAS_INITIALIZE_DATABASE_SCHEMA_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <string>

class AtlasInitializeDatabaseSchema : public AtlasStartupLayerInterface
{
public:
	void Initialize() override;
	std::expected<bool, std::string> Start() override;

private:
	std::expected<bool, std::string> CreateTable(std::string table, std::string query);
	std::expected<bool, std::string> DoesTableExist(std::string table);
	std::expected<bool, std::string> ExecuteStatement(std::string query);

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;

	const std::string FETCH_DOES_TABLE_EXIST = "SELECT COUNT(type) FROM sqlite_master WHERE type = 'table' AND name = ?;";

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
			orientation_angle	REAL	NOT NULL	DEFAULT 0,
			UNIQUE (ra_rad, dec_rad, pm_ra, pm_dec, mag, color_index, object_type, angular_size, orientation_angle)
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

	const std::string CREATE_TRIGGER_INSERT_STAR_INDEX = R"(
		CREATE TRIGGER IF NOT EXISTS TriggerInsertStarIndex
		AFTER INSERT ON StarRenderData
		BEGIN
			INSERT INTO StarIndex (id, minX, maxX, minY, maxY, minZ, maxZ)
			VALUES (
				NEW.id,
				COS(NEW.dec_rad) * COS(NEW.ra_rad), COS(NEW.dec_rad) * COS(NEW.ra_rad),
				COS(NEW.dec_rad) * SIN(NEW.ra_rad), COS(NEW.dec_rad) * SIN(NEW.ra_rad),
				SIN(NEW.dec_rad), SIN(NEW.dec_rad)
			);
		END;
	)";

	const std::string CREATE_TABLE_SETTINGS = R"(
		CREATE TABLE IF NOT EXISTS Settings (
			section	TEXT	NOT NULL,
			key		TEXT	NOT NULL,
			value	TEXT	NOT NULL,
			PRIMARY	KEY	(section, key)
		);
	)";

	const std::string CREATE_TRIGGER_DELETE_STAR_INDEX = R"(
		CREATE TRIGGER IF NOT EXISTS TriggerDeleteStarIndex
		AFTER DELETE ON StarRenderData
		BEGIN
			DELETE FROM StarIndex WHERE id = OLD.id;
		END;
	)";
};

#endif