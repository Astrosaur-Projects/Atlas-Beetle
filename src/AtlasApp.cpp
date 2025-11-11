#include <wx/wx.h>
#include "AtlasGUI/AtlasFrame/AtlasFrame.h"

class AtlasApp : public wxApp
{
public:
    bool OnInit() override;

private:
    AtlasFrame* atlasFrame = nullptr;
};

/*
*
*         .o.           .   oooo                          oooooooooo.                          .   oooo
*        .888.        .o8   `888                          `888'   `Y8b                       .o8   `888
*       .8"888.     .o888oo  888   .oooo.    .oooo.o       888     888  .ooooo.   .ooooo.  .o888oo  888   .ooooo.
*      .8' `888.      888    888  `P  )88b  d88(  "8       888oooo888' d88' `88b d88' `88b   888    888  d88' `88b
*     .88ooo8888.     888    888   .oP"888  `"Y88b.        888    `88b 888ooo888 888ooo888   888    888  888ooo888
*    .8'     `888.    888 .  888  d8(  888  o.  )88b       888    .88P 888    .o 888    .o   888 .  888  888    .o
*   o88o     o8888o   "888" o888o `Y888""8o 8""888P'      o888bood8P'  `Y8bod8P' `Y8bod8P'   "888" o888o `Y8bod8P'
*
*   Project: Atlas Beetle
*
*   Author: Sean Maloney (Astrosaur Projects™)
*
*	Date: October 18, 2025
*
*   Description: A home-brewed, planetarium software with plugin extensibility; built for amateur astronomers, budding computer scientists, and do-it-yourself enthusiasts.
*
*	License: MIT License
*
*	Technologies:
*	 - https://cplusplus.com/
*	 - https://www.opengl.org/
*	 - https://wxwidgets.org/
*	 - https://curl.se/
*	 - https://cmake.org/
*	 - https://sqlite.org/
*/
wxIMPLEMENT_APP(AtlasApp);

bool AtlasApp::OnInit()
{
    atlasFrame = new AtlasFrame();

    atlasFrame->Show(true);

    return true;
}