#include "AtlasGraphics/AtlasFrame.h"

AtlasFrame::AtlasFrame() : wxFrame(nullptr, wxID_ANY, "Atlas Beetle by Astrosaur Projects™")
{
    atlasMenuBar = new AtlasMenuBar();

    SetMenuBar(atlasMenuBar);

    CreateStatusBar();
}

AtlasFrame::~AtlasFrame()
{
}