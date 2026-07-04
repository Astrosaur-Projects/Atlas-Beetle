#ifndef ATLAS_RENDER_LAYER_INTERFACE_H
#define ATLAS_RENDER_LAYER_INTERFACE_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"

class AtlasGraphicsLayerInterface
{
public:
    virtual ~AtlasGraphicsLayerInterface() = default;

    virtual void Initialize() = 0;
    virtual void Render(const AtlasCamera& camera) = 0;
};

#endif