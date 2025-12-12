#include "AtlasMenuOptionEnums.h"
#include "AtlasMenuPlugins.h"
#include "AtlasPluginManager.h"
#include <utility>
#include <wx/event.h>
#include <wx/menu.h>

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