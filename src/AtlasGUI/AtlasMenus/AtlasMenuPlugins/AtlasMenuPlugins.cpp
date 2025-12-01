#include "AtlasGUI/AtlasMenus/AtlasMenuPlugins/AtlasMenuPlugins.h"
#include "AtlasGUI/AtlasMenus/AtlasMenuOptionEnums.h"
#include "AtlasGUI/AtlasPluginManager/AtlasPluginManager.h"

AtlasMenuPlugins::AtlasMenuPlugins() : wxMenu()
{
    this->Append(std::to_underlying(AtlasMenuOptionEnums::ID_PLUGIN_MANAGER), "&Manage", "Add or remove external plugins");

    this->AppendSeparator();

    Bind(wxEVT_MENU, &AtlasMenuPlugins::OnPluginManager, this, std::to_underlying(AtlasMenuOptionEnums::ID_PLUGIN_MANAGER));
}

AtlasMenuPlugins::~AtlasMenuPlugins()
{
}

void AtlasMenuPlugins::OnPluginManager(wxCommandEvent& event)
{
    AtlasPluginManager pluginManagerDialog;

    pluginManagerDialog.ShowModal();
}
