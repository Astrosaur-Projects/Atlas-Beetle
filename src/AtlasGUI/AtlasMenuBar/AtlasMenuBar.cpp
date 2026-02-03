#include "AtlasGUI/AtlasMenuBar/AtlasMenuBar.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuHelp/AtlasMenuHelp.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuPlugins/AtlasMenuPlugins.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuView/AtlasMenuView.h"
#include <wx/menu.h>

AtlasMenuBar::AtlasMenuBar() : wxMenuBar()
{
	fileMenu = new AtlasMenuFile;

	viewMenu = new AtlasMenuView;

	pluginsMenu = new AtlasMenuPlugins;

	helpMenu = new AtlasMenuHelp;

	this->Append(fileMenu, "&File");

	this->Append(viewMenu, "&View");

	this->Append(pluginsMenu, "&Plugins");

	this->Append(helpMenu, "&Help");
}

AtlasMenuBar::~AtlasMenuBar()
{
}