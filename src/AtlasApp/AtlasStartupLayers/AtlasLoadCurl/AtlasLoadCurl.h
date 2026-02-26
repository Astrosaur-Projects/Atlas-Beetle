#ifndef ATLAS_LOAD_CURL_H
#define ATLAS_LOAD_CURL_H

#include "AtlasCore/AtlasStartup/AtlasStartupLayerInterface.h"

class AtlasLoadCurl : public AtlasStartupLayerInterface
{
public:
    std::expected<bool, std::string> Start() override;
};

#endif