#include "AtlasGUI/AtlasPluginManager/AtlasPluginManager.h"

AtlasPluginManager::AtlasPluginManager() : wxDialog(nullptr, wxID_ANY, "Plugin Manager")
{
	pluginManagerSearchControl = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	
	pluginManagerSearchControl->ShowCancelButton(true);

	wxBoxSizer* pluginManagerSizer = new wxBoxSizer(wxVERTICAL);

	pluginManagerSizer->Add(pluginManagerSearchControl, 0, wxALL | wxEXPAND, 5);

	pluginManagerList = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL);

	pluginManagerList->AppendColumn("Name");
	pluginManagerList->AppendColumn("Version");
	pluginManagerList->AppendColumn("Installed");
	pluginManagerList->AppendColumn("Description");
	pluginManagerList->AppendColumn("Tags");

	pluginManagerSizer->Add(pluginManagerList, 1, wxALL | wxEXPAND, 5);

	SetSizerAndFit(pluginManagerSizer);

	Bind(wxEVT_SEARCH, &AtlasPluginManager::OnSearch, this);

}

AtlasPluginManager::~AtlasPluginManager()
{
}

void AtlasPluginManager::OnSearch(wxCommandEvent& event)
{
}