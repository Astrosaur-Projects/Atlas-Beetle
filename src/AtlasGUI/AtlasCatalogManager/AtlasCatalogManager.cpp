#include "AtlasGUI/AtlasCatalogManager/AtlasCatalogManager.h"

AtlasCatalogManager::AtlasCatalogManager() : wxDialog(NULL, wxID_ANY, "Catalog Manager")
{
	searchControl = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	searchControl->ShowCancelButton(true);

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

	boxSizer->Add(searchControl, 0, wxALL | wxEXPAND, 5);

	listView = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL);

	listView->AppendColumn("Name");
	listView->AppendColumn("Type");
	listView->AppendColumn("Enabled");
	listView->AppendColumn("Installed");

	boxSizer->Add(listView, 1, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 5);

	SetSizerAndFit(boxSizer);

	Bind(wxEVT_SEARCH, &AtlasCatalogManager::OnSearch, this);
}


AtlasCatalogManager::~AtlasCatalogManager()
{
}

void AtlasCatalogManager::OnSearch(wxCommandEvent& event)
{
}