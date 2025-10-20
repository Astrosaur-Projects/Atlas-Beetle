#ifndef ATLAS_FRAME_H
#define ATLAS_FRAME_H

#include <wx/wx.h>
#include "AtlasGraphics/AtlasMenuBar/AtlasMenuBar.h"

class AtlasFrame : public wxFrame
{
public:
    AtlasFrame();
    ~AtlasFrame();

private:
    AtlasMenuBar* atlasMenuBar = nullptr;
};

#endif