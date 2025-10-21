#ifndef ATLAS_MENU_BAR_H
#define ATLAS_MENU_BAR_H

#include <wx/wx.h>
#include "AtlasGraphics/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGraphics/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h"

class AtlasMenuBar : public wxMenuBar
{
public:
    AtlasMenuBar();
    ~AtlasMenuBar();

private:
    AtlasMenuFile* atlasMenuFile = nullptr;
    AtlasMenuHelp* atlasMenuHelp = nullptr;

private:
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif