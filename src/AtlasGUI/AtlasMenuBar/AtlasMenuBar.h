#ifndef ATLAS_MENU_BAR_H
#define ATLAS_MENU_BAR_H

#include <wx/wx.h>
#include "AtlasMenuFile.h"
#include "AtlasMenuHelp.h"
#include "AtlasMenuPlugins.h"
#include "AtlasMenuView.h"

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