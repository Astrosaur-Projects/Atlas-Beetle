#include "AtlasGraphics\AtlasMenuOptions\AtlasMenuHelp\AtlasMenuHelp.h"
#include "AtlasGraphics\AtlasMenuOptions\AtlasMenuOptionEnums.h"
#include "AtlasUtilities\AtlasEnumUtilities.h"

AtlasMenuHelp::AtlasMenuHelp() : wxMenu()
{
    this->Append(wxID_ABOUT);

    this->Append(AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_GITHUB), "&GitHub", "Open the Atlas Beetle project repository on GitHub");

    Bind(wxEVT_MENU, &AtlasMenuHelp::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AtlasMenuHelp::OnGitHub, this, AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_GITHUB));
}

AtlasMenuHelp::~AtlasMenuHelp()
{
}

void AtlasMenuHelp::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void AtlasMenuHelp::OnGitHub(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://github.com/SMaloney2017/Atlas-Beetle");
}