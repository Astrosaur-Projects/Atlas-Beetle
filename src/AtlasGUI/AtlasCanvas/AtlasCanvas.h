#ifndef ATLAS_CANVAS_H
#define ATLAS_CANVAS_H

#include <wx/event.h>
#include <wx/glcanvas.h>
#include <wx/frame.h>

class AtlasCanvas : public wxGLCanvas
{
public:
	AtlasCanvas(wxFrame* parent, const wxGLAttributes& glAttributes);
	~AtlasCanvas();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

private:
	wxGLContext* glContext;
};

#endif