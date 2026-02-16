#ifndef ATLAS_IMPORT_DEFAULT_CATALOG_TASK_H
#define ATLAS_IMPORT_DEFAULT_CATALOG_TASK_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <sqlite3.h>
#include <string>

namespace AtlasImportDefaultCatalog
{
	const long STAR_IMPORT_BATCH_SIZE = 10000;

	std::expected<bool, std::string> load();

	std::expected<bool, std::string> loadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog, sqlite3* database);

	bool getSexagesimalUnitsRA(std::string ra, double& raHours, double& raMinutes, double& raSeconds);

	bool getSexagesimalUnitsDE(std::string de, double& deDegrees, double& deMinutes, double& deSeconds);
};

#endif