#ifndef ATLAS_MENU_HELP_H
#define ATLAS_MENU_HELP_H

#include <wx/wx.h>

class AtlasMenuHelp : public wxMenu
{
public:
    AtlasMenuHelp();
    ~AtlasMenuHelp();

private:
    void OnAbout(wxCommandEvent& event);
	void OnGitHub(wxCommandEvent& event);
};

#endif