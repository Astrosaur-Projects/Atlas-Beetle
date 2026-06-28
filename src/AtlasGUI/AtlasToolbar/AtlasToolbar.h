#ifndef ATLAS_MENU_BAR_H
#define ATLAS_MENU_BAR_H

#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuView/AtlasMenuView.h"
#include <wx/menu.h>

class AtlasToolbar : public wxMenuBar
{
public:
	AtlasToolbar();
	~AtlasToolbar();

private:
	AtlasMenuFile* fileMenu = nullptr;
	AtlasMenuView* viewMenu = nullptr;
};

#endif