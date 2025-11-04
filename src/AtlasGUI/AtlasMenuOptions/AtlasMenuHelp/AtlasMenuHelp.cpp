#include "AtlasGUI/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h"
#include "AtlasGUI/AtlasMenuOptions/AtlasMenuOptionEnums.h"
#include "AtlasEnumUtilities.h"

AtlasMenuHelp::AtlasMenuHelp() : wxMenu()
{
    this->Append(wxID_ABOUT);

    Bind(wxEVT_MENU, &AtlasMenuHelp::OnAbout, this, wxID_ABOUT);
}

AtlasMenuHelp::~AtlasMenuHelp()
{
}

void AtlasMenuHelp::OnAbout(wxCommandEvent& event)
{
}