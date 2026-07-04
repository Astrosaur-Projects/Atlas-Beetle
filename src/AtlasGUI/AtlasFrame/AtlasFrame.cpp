#include "AtlasGUI/AtlasCanvas/AtlasCanvas.h"
#include "AtlasGUI/AtlasFrame/AtlasFrame.h"
#include "AtlasGUI/AtlasToolbar/AtlasToolbar.h"
#include <memory>
#include <utility>
#include <wx/defs.h>
#include <wx/event.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/sizer.h>

AtlasFrame::AtlasFrame(std::unique_ptr<AtlasGraphicsEngine> renderSequence) : wxFrame(nullptr, wxID_ANY, "Atlas Beetle by Astrosaur Projects")
{
	wxGLAttributes canvasAttributes;
	canvasAttributes.PlatformDefaults().Defaults().EndList();

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

	if (wxGLCanvas::IsDisplaySupported(canvasAttributes)) {
		canvas = new AtlasCanvas(this, canvasAttributes, std::move(renderSequence));

		boxSizer->Add(canvas, 1, wxEXPAND);
	}

	SetSizerAndFit(boxSizer);

	menuBar = new AtlasToolbar();

	SetMenuBar(menuBar);

	CreateStatusBar();

	Bind(wxEVT_MENU, &AtlasFrame::OnExit, this, wxID_EXIT);
}

AtlasFrame::~AtlasFrame()
{
}

void AtlasFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}