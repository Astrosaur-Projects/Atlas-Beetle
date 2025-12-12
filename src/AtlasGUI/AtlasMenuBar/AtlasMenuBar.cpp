#include "AtlasMenuBar.h"
#include <AtlasMenuFile.h>
#include <AtlasMenuHelp.h>
#include <AtlasMenuPlugins.h>
#include <AtlasMenuView.h>
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