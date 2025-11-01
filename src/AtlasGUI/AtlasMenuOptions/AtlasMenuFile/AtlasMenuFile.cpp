#include "AtlasGUI/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenuOptions/AtlasMenuOptionEnums.h"
#include "AtlasEnumUtilities.h"

AtlasMenuFile::AtlasMenuFile() : wxMenu()
{
    this->Append(AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_HELLO), "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");

    this->AppendSeparator();

    this->Append(wxID_EXIT);

    Bind(wxEVT_MENU, &AtlasMenuFile::OnHello, this, AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_HELLO));
}

AtlasMenuFile::~AtlasMenuFile()
{
}

void AtlasMenuFile::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}