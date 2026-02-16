#ifndef ATLAS_CANVAS_H
#define ATLAS_CANVAS_H

#include <wx/event.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/timer.h>

class AtlasCanvas : public wxGLCanvas
{
public:
	AtlasCanvas(wxFrame* parent, const wxGLAttributes& glAttributes);
	~AtlasCanvas();

private:
	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnTimer(wxTimerEvent& event);

private:
	wxGLContext* glContext;
	wxTimer timer;
};

#endif