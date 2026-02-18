#ifndef ATLAS_CANVAS_H
#define ATLAS_CANVAS_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasQuery/AtlasQuery.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderSky/AtlasRenderSky.h"
#include <memory>
#include <wx/event.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>

class AtlasCanvas : public wxGLCanvas
{
public:
	AtlasCanvas(wxFrame* parent, const wxGLAttributes& glAttributes);
	~AtlasCanvas();

private:
	void InitGraphics();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	void OnMouseDown(wxMouseEvent& event);
	void OnMouseUp(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);

private:
	bool isInitialized = false;
	bool isDragging = false;

	wxPoint lastMousePosition;

	wxGLContext* glContext;

	std::unique_ptr<AtlasCamera> camera;
	std::unique_ptr<AtlasQuery> query;
	std::unique_ptr<AtlasRenderSky> render;
};

#endif