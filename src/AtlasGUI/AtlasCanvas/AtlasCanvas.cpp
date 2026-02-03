#include "AtlasGUI/AtlasCanvas/AtlasCanvas.h"
#include <GL/gl.h>
#include <wx/dcclient.h>
#include <wx/defs.h>
#include <wx/event.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/glcanvas.h>

AtlasCanvas::AtlasCanvas(wxFrame* parent, const wxGLAttributes& glAttributes) : wxGLCanvas(parent, glAttributes, wxID_ANY, wxDefaultPosition, wxSize(900, 600))
{
	wxGLContextAttrs glContextAttributes;
	glContextAttributes.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();

	glContext = new wxGLContext(this, nullptr, &glContextAttributes);

	if (!glContext->IsOK()) {
		delete glContext;
		glContext = nullptr;
	}

	Bind(wxEVT_PAINT, &AtlasCanvas::OnPaint, this);
	Bind(wxEVT_SIZE, &AtlasCanvas::OnSize, this);
}

AtlasCanvas::~AtlasCanvas()
{
	delete glContext;
}

void AtlasCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	SetCurrent(*glContext);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SwapBuffers();
}

void AtlasCanvas::OnSize(wxSizeEvent& event)
{
	wxSize viewPortSize = event.GetSize() * GetContentScaleFactor();

	glViewport(0, 0, viewPortSize.x, viewPortSize.y);

	event.Skip();
}