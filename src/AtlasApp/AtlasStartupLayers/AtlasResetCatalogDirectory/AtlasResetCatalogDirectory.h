#ifndef ATLAS_RESET_CATALOG_DIRECTORY_H
#define ATLAS_RESET_CATALOG_DIRECTORY_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <string>

class AtlasResetCatalogDirectory : public AtlasStartupLayerInterface
{
public:
	void Initialize() override;
	std::expected<bool, std::string> Start() override;

private:
	std::expected<bool, std::string> TruncateCatalogDirectory();
	std::expected<bool, std::string> InsertDefaultCatalogRecord();

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;

	const std::string TRUNCATE_CATALOG_DIRECTORY = "DELETE FROM CatalogDirectory;";

	const std::string INSERT_INTO_CATALOG_DIRECTORY = R"(
        INSERT INTO CatalogDirectory (id, name, source, path)
        VALUES (?, ?, ?, ?);
    )";
};

#endif