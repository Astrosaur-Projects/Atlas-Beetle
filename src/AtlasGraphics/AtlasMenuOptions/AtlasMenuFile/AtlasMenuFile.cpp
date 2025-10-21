#include "AtlasGraphics\AtlasMenuOptions\AtlasMenuFile\AtlasMenuFile.h"

AtlasMenuFile::AtlasMenuFile() : wxMenu()
{
    this->Append(1, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");

    this->AppendSeparator();

    this->Append(wxID_EXIT);

    Bind(wxEVT_MENU, &AtlasMenuFile::OnHello, this, 1);
}

AtlasMenuFile::~AtlasMenuFile()
{
}

void AtlasMenuFile::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
    event.Skip();
}