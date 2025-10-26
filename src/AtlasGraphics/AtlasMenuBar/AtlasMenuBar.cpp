#include "AtlasGraphics/AtlasMenuBar/AtlasMenuBar.h"

AtlasMenuBar::AtlasMenuBar() : wxMenuBar()
{
    atlasMenuFile = new AtlasMenuFile;

    atlasMenuPlugins = new AtlasMenuPlugins;

    atlasMenuHelp = new AtlasMenuHelp;

    this->Append(atlasMenuFile, "&File");

    this->Append(atlasMenuPlugins, "&Plugins");

    this->Append(atlasMenuHelp, "&Help");
}

AtlasMenuBar::~AtlasMenuBar()
{
}