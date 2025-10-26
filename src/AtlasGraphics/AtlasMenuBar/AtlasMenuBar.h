#ifndef ATLAS_MENU_BAR_H
#define ATLAS_MENU_BAR_H

#include <wx/wx.h>
#include "AtlasGraphics/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGraphics/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h"
#include "AtlasGraphics/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.h"
#include "AtlasGraphics/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.h"

class AtlasMenuBar : public wxMenuBar
{
public:
    AtlasMenuBar();
    ~AtlasMenuBar();

private:
    AtlasMenuFile* atlasMenuFile = nullptr;
    AtlasMenuHelp* atlasMenuHelp = nullptr;
    AtlasMenuPlugins* atlasMenuPlugins = nullptr;
    AtlasMenuView* atlasMenuView = nullptr;

private:
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif