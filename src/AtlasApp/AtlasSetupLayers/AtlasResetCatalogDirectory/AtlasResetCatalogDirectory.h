#ifndef ATLAS_RESET_CATALOG_DIRECTORY_H
#define ATLAS_RESET_CATALOG_DIRECTORY_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include <expected>
#include <sqlite3.h>
#include <string>

class AtlasResetCatalogDirectory : public AtlasSetupLayerInterface
{
public:
	void Initialize();
	std::expected<bool, std::string> Setup() override;

private:
	std::expected<bool, std::string> TruncateCatalogDirectory();
	std::expected<bool, std::string> InsertDefaultCatalogRecord();

private:
	sqlite3* database;
};

#endif