#include "AtlasGUI/AtlasMenus/AtlasMenuPlugins/AtlasMenuPlugins.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuOptionEnums.h"
#include "AtlasGUI/AtlasPluginManager/AtlasPluginManager.h"
#include "AtlasEnumUtilities.h"

AtlasMenuPlugins::AtlasMenuPlugins() : wxMenu()
{
    this->Append(AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_PLUGIN_MANAGER), "&Manage", "Add or remove external plugins");

    this->AppendSeparator();

    Bind(wxEVT_MENU, &AtlasMenuPlugins::OnPluginManager, this, AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_PLUGIN_MANAGER));
}

AtlasMenuPlugins::~AtlasMenuPlugins()
{
}

void AtlasMenuPlugins::OnPluginManager(wxCommandEvent& event)
{
    AtlasPluginManager pluginManagerDialog;
    pluginManagerDialog.ShowModal();
}
