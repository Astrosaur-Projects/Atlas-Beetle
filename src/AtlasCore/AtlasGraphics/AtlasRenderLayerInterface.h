#ifndef ATLAS_RENDER_LAYER_INTERFACE_H
#define ATLAS_RENDER_LAYER_INTERFACE_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"

class AtlasRenderLayerInterface
{
public:
    virtual ~AtlasRenderLayerInterface() = default;

    virtual void Initialize() = 0;
    virtual void Render(const AtlasCamera& camera) = 0;
};

#endif