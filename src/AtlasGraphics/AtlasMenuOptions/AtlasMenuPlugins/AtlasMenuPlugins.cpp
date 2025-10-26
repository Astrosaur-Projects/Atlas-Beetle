#include <AtlasGraphics/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.h>
#include <AtlasGraphics/AtlasMenuOptions/AtlasMenuOptionEnums.h>
#include <AtlasGraphics/AtlasPluginManager/AtlasPluginManager.h>
#include <AtlasUtilities/AtlasEnumUtilities.h>

AtlasMenuPlugins::AtlasMenuPlugins() : wxMenu()
{
    this->Append(AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_PLUGIN_MANAGER), "&Manage", "Add or remove external plugins");

    this->AppendSeparator();

    Bind(wxEVT_MENU, &AtlasMenuPlugins::OnManage, this, AtlasEnumUtilities::getValue(AtlasMenuOptionEnums::ID_PLUGIN_MANAGER));
}

AtlasMenuPlugins::~AtlasMenuPlugins()
{
}

void AtlasMenuPlugins::OnManage(wxCommandEvent& event)
{
    AtlasPluginManager pluginManagerDialog;
    pluginManagerDialog.ShowModal();
}
