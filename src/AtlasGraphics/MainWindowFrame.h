#ifndef ATLAS_MAIN_WINDOW_FRAME_H
#define ATLAS_MAIN_WINDOW_FRAME_H

#include <wx/wx.h>

class MainWindowFrame : public wxFrame
{
public: MainWindowFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif