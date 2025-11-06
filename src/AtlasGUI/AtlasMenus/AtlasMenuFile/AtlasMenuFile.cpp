#include "AtlasGUI/AtlasMenus/AtlasMenuFile/AtlasMenuFile.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuOptionEnums.h"
#include "AtlasGUI/AtlasCatalogManager/AtlasCatalogManager.h"
#include "AtlasEnumUtilities.h"

AtlasMenuFile::AtlasMenuFile() : wxMenu()
{
    this->Append(AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_CATALOG_MANAGER), "&Catalogs", "Add or remove astronomical catalogs");

    this->AppendSeparator();

    this->Append(wxID_EXIT);

    Bind(wxEVT_MENU, &AtlasMenuFile::OnCatalogManager, this, AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_CATALOG_MANAGER));
}

AtlasMenuFile::~AtlasMenuFile()
{
}

void AtlasMenuFile::OnCatalogManager(wxCommandEvent& event)
{
    AtlasCatalogManager atlasCatalogManager;
    atlasCatalogManager.ShowModal();
}