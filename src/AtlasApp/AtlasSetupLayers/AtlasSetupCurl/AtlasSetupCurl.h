#ifndef ATLAS_SETUP_CURL_H
#define ATLAS_SETUP_CURL_H

#include "AtlasCore/AtlasStartup/AtlasSetupLayerInterface.h"

class AtlasSetupCurl : public AtlasSetupLayerInterface
{
public:
    std::expected<bool, std::string> Setup() override;
};

#endif