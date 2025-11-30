#ifndef ATLAS_FRAME_H
#define ATLAS_FRAME_H

#include <wx/wx.h>
#include "AtlasGUI/AtlasMenuBar/AtlasMenuBar.h"
#include "AtlasGUI/AtlasCanvas/AtlasCanvas.h"

class AtlasFrame : public wxFrame
{
public:
    AtlasFrame();
    ~AtlasFrame();

private:
    AtlasMenuBar* menuBar = nullptr;
    AtlasCanvas* canvas = nullptr;

private:
    void OnExit(wxCommandEvent& event);
};

#endif