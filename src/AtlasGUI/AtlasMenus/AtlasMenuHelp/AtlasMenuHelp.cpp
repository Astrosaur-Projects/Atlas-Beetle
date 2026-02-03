#include "AtlasGUI/AtlasMenus/AtlasMenuHelp/AtlasMenuHelp.h"
#include <wx/defs.h>
#include <wx/event.h>
#include <wx/menu.h>

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