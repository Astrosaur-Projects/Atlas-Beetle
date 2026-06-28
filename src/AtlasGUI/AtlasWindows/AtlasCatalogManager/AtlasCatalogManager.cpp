#include "AtlasApp/AtlasQueryObjects/AtlasQueryCatalogDirectory/AtlasQueryCatalogDirectory.h"
#include "AtlasGUI/AtlasWindows/AtlasCatalogManager/AtlasCatalogManager.h"
#include "AtlasUtilities/AtlasCatalogUtilities/AtlasCatalogUtilities.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <memory>
#include <string>
#include <vector>
#include <wx/defs.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/listbase.h>
#include <wx/listctrl.h>
#include <wx/panel.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>
#include <wx/string.h>
#include <wx/toplevel.h>
#include <wx/treebase.h>
#include <wx/treectrl.h>

AtlasCatalogManager::AtlasCatalogManager() : wxDialog(NULL, wxID_ANY, "Catalog Manager", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	catalogDirectoryQueryObject = std::make_unique<AtlasQueryCatalogDirectory>();

	Initialize();

	std::string catalogDirectoryPath = AtlasDirectoryUtilities::GetDirectoryPath(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_CATALOGS);

	wxTreeItemId catalogDirectoryRootId = directoryTree->AddRoot("Root");

	BuildDirectoryTree();
}

void AtlasCatalogManager::Initialize()
{
	searchControl = new wxSearchCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	searchControl->ShowCancelButton(true);

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(searchControl, 0, wxALL | wxEXPAND, 5);

	mainSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);
	mainSplitter->SetMinimumPaneSize(150);

	rightSplitter = new wxSplitterWindow(mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);
	rightSplitter->SetMinimumPaneSize(100);

	directoryTree = new wxTreeCtrl(mainSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT);

	filePreview = new wxPanel(rightSplitter, wxID_ANY);
	filePreview->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

	fileDetails = new wxListView(rightSplitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);
	fileDetails->AppendColumn("Property", wxLIST_FORMAT_LEFT, 100);
	fileDetails->AppendColumn("Value", wxLIST_FORMAT_LEFT, 300);

	rightSplitter->SplitHorizontally(filePreview, fileDetails);

	mainSplitter->SplitVertically(directoryTree, rightSplitter);

	boxSizer->Add(mainSplitter, 1, wxALL | wxEXPAND, 5);

	wxSizer* buttonSizer = CreateStdDialogButtonSizer(wxOK | wxCANCEL);
	if (buttonSizer) { boxSizer->Add(buttonSizer, 0, wxALL | wxEXPAND, 5); }

	SetSizerAndFit(boxSizer);
	Center();

	Bind(wxEVT_SEARCH, &AtlasCatalogManager::OnSearch, this);
	directoryTree->Bind(wxEVT_TREE_SEL_CHANGED, &AtlasCatalogManager::OnTreeSelectionChanged, this);
}

void AtlasCatalogManager::BuildDirectoryTree()
{
	std::expected<std::vector<AtlasCatalogUtilities::CatalogRecord>, std::string> queryCatalogDirectoryResult = catalogDirectoryQueryObject->Query();
}

void AtlasCatalogManager::OnTreeSelectionChanged(wxTreeEvent& event)
{
}

void AtlasCatalogManager::OnSearch(wxCommandEvent& event)
{
}