#include "AtlasGUI/AtlasToolbar/AtlasToolbar.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuView/AtlasMenuView.h"
#include <wx/menu.h>

AtlasToolbar::AtlasToolbar() : wxMenuBar()
{
	fileMenu = new AtlasMenuFile;

	viewMenu = new AtlasMenuView;

	Append(fileMenu, "&File");

	Append(viewMenu, "&View");
}

AtlasToolbar::~AtlasToolbar()
{
}