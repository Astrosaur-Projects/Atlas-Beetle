#include "AtlasGUI/AtlasCatalogManager/AtlasCatalogManager.h"

AtlasCatalogManager::AtlasCatalogManager() : wxDialog(NULL, wxID_ANY, "Catalog Manager")
{
	catalogManagerSearchControl = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	catalogManagerSearchControl->ShowCancelButton(true);

	wxBoxSizer* catalogManagerSizer = new wxBoxSizer(wxVERTICAL);

	catalogManagerSizer->Add(catalogManagerSearchControl, 0, wxALL | wxEXPAND, 5);

	catalogManagerList = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL);

	catalogManagerList->AppendColumn("Name");
	catalogManagerList->AppendColumn("Type");
	catalogManagerList->AppendColumn("Enabled");

	catalogManagerSizer->Add(catalogManagerList, 1, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 5);

	SetSizerAndFit(catalogManagerSizer);

	Bind(wxEVT_SEARCH, &AtlasCatalogManager::OnSearch, this);
}


AtlasCatalogManager::~AtlasCatalogManager()
{
}

void AtlasCatalogManager::OnSearch(wxCommandEvent& event)
{
}