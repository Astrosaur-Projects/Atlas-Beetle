#ifndef ATLAS_MENU_FILE_H
#define ATLAS_MENU_FILE_H

#include <wx/wx.h>

class AtlasMenuFile : public wxMenu
{
public:
    AtlasMenuFile();
    ~AtlasMenuFile();

private:
    void OnHello(wxCommandEvent& event);
};

#endif