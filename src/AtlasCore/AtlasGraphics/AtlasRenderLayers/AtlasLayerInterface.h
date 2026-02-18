#ifndef ATLAS_ATLAS_LAYER_INTERFACE_H
#define ATLAS_ATLAS_LAYER_INTERFACE_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"

class AtlasLayerInterface
{
public:
    virtual ~AtlasLayerInterface() = default;

    virtual void Initialize() = 0;
    virtual void Render(const AtlasCamera& camera) = 0;
};

#endif