#include "AtlasCatalogManager.h"
#include "AtlasMenuFile.h"
#include "AtlasMenuOptionEnums.h"
#include <utility>
#include <wx/defs.h>
#include <wx/event.h>
#include <wx/menu.h>

AtlasMenuFile::AtlasMenuFile() : wxMenu()
{
	this->Append(std::to_underlying(AtlasMenuOptionEnums::ID_CATALOG_MANAGER), "&Catalogs", "Add or remove astronomical catalogs");

	this->AppendSeparator();

	this->Append(wxID_EXIT);

	Bind(wxEVT_MENU, &AtlasMenuFile::OnCatalogManager, this, std::to_underlying(AtlasMenuOptionEnums::ID_CATALOG_MANAGER));
}

AtlasMenuFile::~AtlasMenuFile()
{
}

void AtlasMenuFile::OnCatalogManager(wxCommandEvent& event)
{
	AtlasCatalogManager catalogManagerDialog;

	catalogManagerDialog.ShowModal();
}