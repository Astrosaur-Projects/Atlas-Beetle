#include "AtlasGraphics/AtlasMenuBar/AtlasMenuBar.h"

AtlasMenuBar::AtlasMenuBar() : wxMenuBar()
{
    menuFile = new wxMenu;
    menuFile->Append(1, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    menuView = new wxMenu;

    menuExtensions = new wxMenu;

    menuWindow = new wxMenu;

    menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    this->Append(menuFile, "&File");
    this->Append(menuView, "&View");
    this->Append(menuExtensions, "&Extensions");
    this->Append(menuWindow, "&Window");
    this->Append(menuHelp, "&Help");

    Bind(wxEVT_MENU, &AtlasMenuBar::OnHello, this, 1);
    Bind(wxEVT_MENU, &AtlasMenuBar::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &AtlasMenuBar::OnExit, this, wxID_EXIT);
}

AtlasMenuBar::~AtlasMenuBar()
{
}

void AtlasMenuBar::OnExit(wxCommandEvent& event)
{
    Close(true);
    event.Skip();
}

void AtlasMenuBar::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
    event.Skip();
}

void AtlasMenuBar::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
    event.Skip();
}