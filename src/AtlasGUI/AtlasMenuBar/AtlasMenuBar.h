#ifndef ATLAS_MENU_BAR_H
#define ATLAS_MENU_BAR_H

#include <wx/wx.h>
#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuHelp/AtlasMenuHelp.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuPlugins/AtlasMenuPlugins.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuView/AtlasMenuView.h"

class AtlasMenuBar : public wxMenuBar
{
public:
    AtlasMenuBar();
    ~AtlasMenuBar();
    
private:
    AtlasMenuFile* fileMenu = nullptr;
    AtlasMenuHelp* helpMenu = nullptr;
    AtlasMenuPlugins* pluginsMenu = nullptr;
    AtlasMenuView* viewMenu = nullptr;

private:
    void OnAbout(wxCommandEvent& event);
};

#endif