#ifndef ATLAS_IMPORT_DEFAULT_CATALOG_TASK_H
#define ATLAS_IMPORT_DEFAULT_CATALOG_TASK_H

#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include <expected>
#include <fitsio.h>
#include <string>
#include <vector>

namespace AtlasImportDefaultCatalog
{
	const long STAR_IMPORT_BATCH_SIZE = 10000;

	std::expected<bool, std::string> load();
	std::expected<bool, std::string> loadCatalog(const AtlasCatalogUtilities::CatalogRecord catalog);
	std::expected<bool, std::string> fitsOpenFile(fitsfile* filePointer, std::string filePath, long* totalRows);
	std::expected<bool, std::string> fitsCloseFile(fitsfile* filePointer, std::string filePath);
	std::expected<bool, std::string> fitsGetColumnIndex(fitsfile* filePointer, std::string columnHeader, int* columnIndex);
	std::expected<bool, std::string> fitsLoadColumnIntoBuffer(fitsfile* filePointer, int columnIndex, int importBatchIndex, long importBatchSize, std::vector<double>& dataBuffer);
	std::expected<bool, std::string> fitsLoadColumnIntoBuffer(fitsfile* filePointer, int columnIndex, int importBatchIndex, long importBatchSize, std::vector<float>& dataBuffer);
	std::expected<bool, std::string> fitsLoadColumnIntoBuffer(fitsfile* filePointer, int columnIndex, int importBatchIndex, long importBatchSize, std::vector<std::string>& dataBuffer);
	bool getSexagesimalUnitsRA(std::string ra, double& raHours, double& raMinutes, double& raSeconds);
	bool getSexagesimalUnitsDE(std::string de, double& deDegrees, double& deMinutes, double& deSeconds);
};

#endif