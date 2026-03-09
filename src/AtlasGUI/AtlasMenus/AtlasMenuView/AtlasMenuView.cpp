#include "AtlasGUI/AtlasCatalogManager/AtlasCatalogManager.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuOptionEnums.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuView/AtlasMenuView.h"
#include <utility>
#include <wx/event.h>
#include <wx/menu.h>

AtlasMenuView::AtlasMenuView() : wxMenu()
{
	Append(std::to_underlying(AtlasMenuOptionEnums::ID_CATALOG_MANAGER), "&Catalog Manager", "Add, edit, and remove astronomical catalogs");

	Bind(wxEVT_MENU, &AtlasMenuView::OnCatalogManager, this, std::to_underlying(AtlasMenuOptionEnums::ID_CATALOG_MANAGER));
}

AtlasMenuView::~AtlasMenuView()
{
}

void AtlasMenuView::OnCatalogManager(wxCommandEvent& event)
{
	AtlasCatalogManager catalogManagerDialog;

	catalogManagerDialog.ShowModal();
}