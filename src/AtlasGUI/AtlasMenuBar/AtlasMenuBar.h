#ifndef ATLAS_MENU_BAR_H
#define ATLAS_MENU_BAR_H

#include "AtlasMenuFile.h"
#include "AtlasMenuHelp.h"
#include "AtlasMenuPlugins.h"
#include "AtlasMenuView.h"
#include <wx/event.h>
#include <wx/menu.h>

class AtlasMenuBar : public wxMenuBar
{
public:
	AtlasMenuBar();
	~AtlasMenuBar();

private:
	AtlasMenuFile* fileMenu = nullptr;
	AtlasMenuHelp* helpMenu = nullptr;
	AtlasMenuPlugins* pluginsMenu = nullptr;
	AtlasMenuView* viewMenu = nullptr;

private:
	void OnAbout(wxCommandEvent& event);
};

#endif