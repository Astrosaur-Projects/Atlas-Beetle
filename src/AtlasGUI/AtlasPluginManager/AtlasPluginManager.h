#ifndef ATLAS_PLUGIN_MANAGER_H
#define ATLAS_PLUGIN_MANAGER_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/srchctrl.h>

class AtlasPluginManager : public wxDialog
{
public:
	AtlasPluginManager();
	~AtlasPluginManager();

private:
	wxSearchCtrl* searchControl = nullptr;
	wxListView* listView = nullptr;

private:
	void OnSearch(wxCommandEvent& event);
};

#endif