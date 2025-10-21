#include "AtlasGraphics/AtlasFrame/AtlasFrame.h"

AtlasFrame::AtlasFrame() : wxFrame(nullptr, wxID_ANY, "Atlas Beetle by Astrosaur Projects™")
{
    atlasMenuBar = new AtlasMenuBar();

    SetMenuBar(atlasMenuBar);

    CreateStatusBar();

    Bind(wxEVT_MENU, &AtlasFrame::OnExit, this, wxID_EXIT);
}

AtlasFrame::~AtlasFrame()
{
}

void AtlasFrame::OnExit(wxCommandEvent& event)
{
    Close(true);

    event.Skip();
}