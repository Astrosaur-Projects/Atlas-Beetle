#ifndef ATLAS_MENU_VIEW_H
#define ATLAS_MENU_VIEW_H

#include <wx/menu.h>

class AtlasMenuView : public wxMenu
{
public:
	AtlasMenuView();
	~AtlasMenuView();

private:
	void OnCatalogManager(wxCommandEvent& event);
};

#endif