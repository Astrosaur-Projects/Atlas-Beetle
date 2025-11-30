#ifndef ATLAS_CATALOG_MANAGER_H
#define ATLAS_CATALOG_MANAGER_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/srchctrl.h>

class AtlasCatalogManager : public wxDialog
{
public:
	AtlasCatalogManager();
	~AtlasCatalogManager();

private:
	wxSearchCtrl* searchControl = nullptr;
	wxListView* listView = nullptr;

private:
	void OnSearch(wxCommandEvent& event);
};

#endif