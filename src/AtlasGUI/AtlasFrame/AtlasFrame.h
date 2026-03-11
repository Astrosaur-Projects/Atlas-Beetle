#ifndef ATLAS_FRAME_H
#define ATLAS_FRAME_H

#include "AtlasCore/AtlasGraphics/AtlasRenderSky/AtlasRenderSky.h"
#include "AtlasGUI/AtlasCanvas/AtlasCanvas.h"
#include "AtlasGUI/AtlasMenuBar/AtlasMenuBar.h"
#include <memory>
#include <wx/event.h>
#include <wx/frame.h>

class AtlasFrame : public wxFrame
{
public:
	AtlasFrame(std::unique_ptr<AtlasRenderSky> render);
	~AtlasFrame();

private:
	AtlasMenuBar* menuBar = nullptr;
	AtlasCanvas* canvas = nullptr;

private:
	void OnExit(wxCommandEvent& event);
};

#endif