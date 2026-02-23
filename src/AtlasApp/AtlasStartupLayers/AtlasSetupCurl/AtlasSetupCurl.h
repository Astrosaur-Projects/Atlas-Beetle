#ifndef ATLAS_SETUP_CURL_H
#define ATLAS_SETUP_CURL_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"

class AtlasSetupCurl : public AtlasStartupLayerInterface
{
public:
    std::expected<bool, std::string> Start() override;
};

#endif