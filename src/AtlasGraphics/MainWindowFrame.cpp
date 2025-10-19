#include "AtlasGraphics/MainWindowFrame.h"

MainWindowFrame::MainWindowFrame() : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(1, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &MainWindowFrame::OnHello, this, 1);
    Bind(wxEVT_MENU, &MainWindowFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindowFrame::OnExit, this, wxID_EXIT);
}

void MainWindowFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainWindowFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MainWindowFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}