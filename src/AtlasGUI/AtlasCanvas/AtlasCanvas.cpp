#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasGraphicsEngine/AtlasGraphicsEngine.h"
#include "AtlasGUI/AtlasCanvas/AtlasCanvas.h"
#include <GL/glew.h>
#include <glm/trigonometric.hpp>
#include <memory>
#include <wx/dcclient.h>
#include <wx/defs.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/glcanvas.h>

AtlasCanvas::AtlasCanvas(wxFrame* parent, const wxGLAttributes& glAttributes, std::unique_ptr<AtlasGraphicsEngine> renderSequence) : wxGLCanvas(parent, glAttributes, wxID_ANY, wxDefaultPosition, wxSize(900, 600))
{
	wxGLContextAttrs glContextAttributes;
	glContextAttributes.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();

	glContext = new wxGLContext(this, nullptr, &glContextAttributes);

	if (!glContext->IsOK()) {
		delete glContext;
		glContext = nullptr;
	}

	camera = std::make_unique<AtlasCamera>(900.0f, 600.0f);
	camera->SetDirection(1.46f, 0.096f);

	render = std::move(renderSequence);

	Bind(wxEVT_PAINT, &AtlasCanvas::OnPaint, this);
	Bind(wxEVT_SIZE, &AtlasCanvas::OnSize, this);
	Bind(wxEVT_MOUSEWHEEL, &AtlasCanvas::OnMouseWheel, this);
	Bind(wxEVT_LEFT_DOWN, &AtlasCanvas::OnMouseDown, this);
	Bind(wxEVT_LEFT_UP, &AtlasCanvas::OnMouseUp, this);
	Bind(wxEVT_MOTION, &AtlasCanvas::OnMouseMove, this);
}

AtlasCanvas::~AtlasCanvas()
{
	delete glContext;
}

void AtlasCanvas::InitGraphics()
{
	if (glewInit() != GLEW_OK) { return; }

	render->Initialize();

	isInitialized = true;
}

void AtlasCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	SetCurrent(*glContext);

	if (!isInitialized) {
		InitGraphics();
	}

	if (render && camera) {
		render->Render(*camera);
	}

	SwapBuffers();
}

void AtlasCanvas::OnSize(wxSizeEvent& event)
{
	wxSize viewPortSize = event.GetSize() * GetContentScaleFactor();

	glViewport(0, 0, viewPortSize.x, viewPortSize.y);

	camera->SetAspectRatio((float)viewPortSize.x, (float)viewPortSize.y);

	event.Skip();
}

void AtlasCanvas::OnMouseWheel(wxMouseEvent& event)
{
	if (!camera) { return; }

	double zoom = 2.0;
	double fov = camera->GetFOV();

	if (event.GetWheelRotation() > 0) {
		fov -= zoom;
	} else {
		fov += zoom;
	}

	camera->SetZoom(fov);

	Refresh();

	event.Skip();
}

void AtlasCanvas::OnMouseDown(wxMouseEvent& event)
{
	isDragging = true;
	lastMousePosition = event.GetPosition();

	if (!HasCapture()) {
		CaptureMouse();
	}

	event.Skip();
}

void AtlasCanvas::OnMouseUp(wxMouseEvent& event)
{
	isDragging = false;

	if (HasCapture()) {
		ReleaseMouse();
	}

	event.Skip();
}

void AtlasCanvas::OnMouseMove(wxMouseEvent& event)
{
	if (isDragging && camera) {
		wxPoint currentPos = event.GetPosition();

		int dX = currentPos.x - lastMousePosition.x;
		int dY = currentPos.y - lastMousePosition.y;

		lastMousePosition = currentPos;

		float fovRadians = glm::radians(camera->GetFOV());

		float sensitivity = fovRadians / GetSize().x;

		camera->Pan(-dX * sensitivity, dY * sensitivity);

		Refresh();
	}

	event.Skip();
}