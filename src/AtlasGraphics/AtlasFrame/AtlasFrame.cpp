#include "AtlasGraphics/AtlasFrame/AtlasFrame.h"

AtlasFrame::AtlasFrame() : wxFrame(nullptr, wxID_ANY, "Atlas Beetle by Astrosaur Projects™")
{
    wxGLAttributes canvasAttributes;
    canvasAttributes.PlatformDefaults().Defaults().EndList();

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);

    if (wxGLCanvas::IsDisplaySupported(canvasAttributes))
    {
        atlasCanvas = new AtlasCanvas(this, canvasAttributes);

        frameSizer->Add(atlasCanvas, 1, wxEXPAND);
    }

    SetSizerAndFit(frameSizer);
    
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
}