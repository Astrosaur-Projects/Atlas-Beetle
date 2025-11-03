#include "AtlasGUI/AtlasCatalogManager/AtlasCatalogManager.h"

AtlasCatalogManager::AtlasCatalogManager() : wxDialog(NULL, wxID_ANY, "Catalog Manager")
{
	catalogManagerList = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL);

	catalogManagerList->AppendColumn("Name");
	catalogManagerList->AppendColumn("Type");
	catalogManagerList->AppendColumn("Enabled");

	wxBoxSizer* catalogManagerSizer = new wxBoxSizer(wxVERTICAL);

	catalogManagerSizer->Add(catalogManagerList, 1, wxALL | wxEXPAND, 5);

	SetSizerAndFit(catalogManagerSizer);
}


AtlasCatalogManager::~AtlasCatalogManager()
{
}