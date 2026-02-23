#ifndef ATLAS_SETUP_DEFAULT_CATALOG_H
#define ATLAS_SETUP_DEFAULT_CATALOG_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

class AtlasSetupDefaultCatalog : public AtlasSetupLayerInterface
{
public:
	void Initialize();
	std::expected<bool, std::string> Setup() override;

private:
	std::expected<bool, std::string> LoadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog);
	std::expected<bool, std::string> Insert(std::vector<AtlasStar> buffer);
	std::expected<bool, std::string> InsertStarRenderData(std::vector<AtlasStar> buffer);

	bool GetSexagesimalUnitsRA(std::string ra, double& raHours, double& raMinutes, double& raSeconds);
	bool GetSexagesimalUnitsDE(std::string de, int& sign, double& deDegrees, double& deMinutes, double& deSeconds);

private:
	sqlite3* database;

	const long STAR_IMPORT_BATCH_SIZE = 10000;

	const std::string INSERT_STAR_RENDER_DATA_STATEMENT = "INSERT OR IGNORE INTO StarRenderData (ra_rad, dec_rad, pm_ra, pm_dec, mag, color_index, object_type) VALUES (?, ?, ?, ?, ?, ?, ?);";
	
	const std::string BEGIN_TRANSACTION = "BEGIN TRANSACTION;";

	const std::string ROLLBACK_TRANSACTION = "ROLLBACK;";

	const std::string COMMIT_TRANSACTION = "COMMIT;";
};

#endif