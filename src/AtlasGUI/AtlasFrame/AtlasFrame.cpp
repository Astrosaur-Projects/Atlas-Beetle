#include "AtlasGUI/AtlasFrame/AtlasFrame.h"

AtlasFrame::AtlasFrame() : wxFrame(nullptr, wxID_ANY, "Atlas Beetle by Astrosaur Projects™")
{
    wxGLAttributes canvasAttributes;
    canvasAttributes.PlatformDefaults().Defaults().EndList();

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    if (wxGLCanvas::IsDisplaySupported(canvasAttributes))
    {
        canvas = new AtlasCanvas(this, canvasAttributes);

        boxSizer->Add(canvas, 1, wxEXPAND);
    }

    SetSizerAndFit(boxSizer);
    
    menuBar = new AtlasMenuBar();

    SetMenuBar(menuBar);

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