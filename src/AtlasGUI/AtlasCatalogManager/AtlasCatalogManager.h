#ifndef ATLAS_CATALOG_MANAGER_H
#define ATLAS_CATALOG_MANAGER_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class AtlasCatalogManager : public wxDialog
{
public:
	AtlasCatalogManager();
	~AtlasCatalogManager();

private:
	wxListView* catalogManagerList = nullptr;
};

#endif