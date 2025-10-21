#include "AtlasGraphics/AtlasMenuBar/AtlasMenuBar.h"

AtlasMenuBar::AtlasMenuBar() : wxMenuBar()
{
    atlasMenuFile = new AtlasMenuFile;

    atlasMenuHelp = new AtlasMenuHelp;

    this->Append(atlasMenuFile, "&File");

    this->Append(atlasMenuHelp, "&Help");
}

AtlasMenuBar::~AtlasMenuBar()
{
}