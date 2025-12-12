#ifndef ATLAS_MENU_PLUGINS_H
#define ATLAS_MENU_PLUGINS_H

#include <wx/event.h>
#include <wx/menu.h>

class AtlasMenuPlugins : public wxMenu
{
public:
	AtlasMenuPlugins();
	~AtlasMenuPlugins();

private:
	void OnPluginManager(wxCommandEvent& event);
};

#endif