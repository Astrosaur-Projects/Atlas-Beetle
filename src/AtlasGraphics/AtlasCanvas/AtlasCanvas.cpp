#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "AtlasGraphics/AtlasCanvas/AtlasCanvas.h"

AtlasCanvas::AtlasCanvas(wxFrame* parent, const wxGLAttributes& canvasAttributes) : wxGLCanvas(parent, canvasAttributes, wxID_ANY, wxDefaultPosition, wxSize(900, 600))
{
	wxGLContextAttrs canvasContextAttributes;
	canvasContextAttributes.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();

	canvasContext = new wxGLContext(this, nullptr, &canvasContextAttributes);

	if (!canvasContext->IsOK())
	{
		delete canvasContext;
		canvasContext = nullptr;
	}

	Bind(wxEVT_PAINT, &AtlasCanvas::OnPaint, this);
	Bind(wxEVT_SIZE, &AtlasCanvas::OnSize, this);
}

AtlasCanvas::~AtlasCanvas()
{
	delete canvasContext;
}

void AtlasCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
}

void AtlasCanvas::OnSize(wxSizeEvent& event)
{
	wxSize viewPortSize = event.GetSize() * GetContentScaleFactor();

	glViewport(0, 0, viewPortSize.x, viewPortSize.y);

	event.Skip();
}