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

	bool GetSexagesimalUnitsRA(std::string ra, double& raHours, double& raMinutes, double& raSeconds);

	bool GetSexagesimalUnitsDE(std::string de, int& sign, double& deDegrees, double& deMinutes, double& deSeconds);

private:
	sqlite3* database;

	const long STAR_IMPORT_BATCH_SIZE = 10000;
};

#endif