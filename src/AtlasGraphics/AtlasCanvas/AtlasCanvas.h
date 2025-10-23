#ifndef ATLAS_CANVAS_H
#define ATLAS_CANVAS_H

#include <wx/wx.h>
#include <wx/glcanvas.h>

class AtlasCanvas : public wxGLCanvas
{
public:
	AtlasCanvas(wxFrame* parent, const wxGLAttributes& canvasAttributes);
	~AtlasCanvas();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

private:
	wxGLContext* canvasContext;
};

#endif