#ifndef ATLAS_MENU_HELP_H
#define ATLAS_MENU_HELP_H

#include <wx/event.h>
#include <wx/menu.h>

class AtlasMenuHelp : public wxMenu
{
public:
	AtlasMenuHelp();
	~AtlasMenuHelp();

private:
	void OnAbout(wxCommandEvent& event);
};

#endif