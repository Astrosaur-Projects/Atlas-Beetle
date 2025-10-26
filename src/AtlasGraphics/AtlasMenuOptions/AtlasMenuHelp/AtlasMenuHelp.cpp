#include <AtlasGraphics/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h>
#include <AtlasGraphics/AtlasMenuOptions/AtlasMenuOptionEnums.h>
#include <AtlasUtilities/AtlasEnumUtilities.h>

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
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}