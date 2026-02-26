#ifndef ATLAS_SETUP_DIRECTORY_H
#define ATLAS_SETUP_DIRECTORY_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <string>

class AtlasCreateApplicationDirectory : public AtlasStartupLayerInterface
{
public:
	std::expected<bool, std::string> Start() override;
private:
	std::expected<bool, std::string> InitDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory);
};

#endif