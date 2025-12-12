#ifndef ATLAS_MENU_FILE_H
#define ATLAS_MENU_FILE_H

#include <wx/event.h>
#include <wx/menu.h>

class AtlasMenuFile : public wxMenu
{
public:
	AtlasMenuFile();
	~AtlasMenuFile();

private:
	void OnCatalogManager(wxCommandEvent& event);
};

#endif