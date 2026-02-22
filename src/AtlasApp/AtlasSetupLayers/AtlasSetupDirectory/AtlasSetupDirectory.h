#ifndef ATLAS_SETUP_DIRECTORY_H
#define ATLAS_SETUP_DIRECTORY_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <string>

class AtlasSetupDirectory : public AtlasSetupLayerInterface
{
public:
	std::expected<bool, std::string> Setup() override;
private:
	std::expected<bool, std::string> InitDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory);
};

#endif