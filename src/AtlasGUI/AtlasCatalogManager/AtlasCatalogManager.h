#ifndef ATLAS_CATALOG_MANAGER_H
#define ATLAS_CATALOG_MANAGER_H

#include "AtlasApp/AtlasQueryObjects/AtlasQueryCatalogDirectory/AtlasQueryCatalogDirectory.h"
#include <memory>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/listctrl.h>
#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>
#include <wx/treebase.h>
#include <wx/treectrl.h>

class AtlasCatalogManager : public wxDialog
{
public:
	AtlasCatalogManager();

private:
	std::unique_ptr<AtlasQueryCatalogDirectory> catalogDirectoryQueryObject;

	wxSearchCtrl* searchControl = nullptr;

	wxSplitterWindow* mainSplitter = nullptr;
	wxSplitterWindow* rightSplitter = nullptr;

	wxTreeCtrl* directoryTree = nullptr;
	wxPanel* filePreview = nullptr;
	wxListView* fileDetails = nullptr;

private:
	void Initialize();
	void BuildDirectoryTree();

	void OnSearch(wxCommandEvent& event);
	void OnTreeSelectionChanged(wxTreeEvent& event);
};

#endif