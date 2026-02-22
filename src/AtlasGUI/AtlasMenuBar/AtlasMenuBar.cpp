#include "AtlasGUI/AtlasMenuBar/AtlasMenuBar.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuView/AtlasMenuView.h"
#include <wx/menu.h>

AtlasMenuBar::AtlasMenuBar() : wxMenuBar()
{
	fileMenu = new AtlasMenuFile;

	viewMenu = new AtlasMenuView;

	this->Append(fileMenu, "&File");

	this->Append(viewMenu, "&View");
}

AtlasMenuBar::~AtlasMenuBar()
{
}