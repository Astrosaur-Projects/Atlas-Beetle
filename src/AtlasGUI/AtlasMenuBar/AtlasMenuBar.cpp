#include "AtlasMenuBar.h"

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