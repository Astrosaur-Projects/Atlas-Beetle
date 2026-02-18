#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasQuery/AtlasQuery.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayers/AtlasRenderHorizon/AtlasRenderHorizon.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayers/AtlasRenderStars/AtlasRenderStars.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderSky/AtlasRenderSky.h"
#include "AtlasGUI/AtlasCanvas/AtlasCanvas.h"
#include <GL/glew.h>
#include <memory>
#include <utility>
#include <wx/dcclient.h>
#include <wx/defs.h>
#include <wx/event.h>
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

	camera = std::make_unique<AtlasCamera>(900.0f, 600.0f);
	camera->SetDirection(1.46f, 0.096f);

	Bind(wxEVT_PAINT, &AtlasCanvas::OnPaint, this);
	Bind(wxEVT_SIZE, &AtlasCanvas::OnSize, this);
	Bind(wxEVT_MOUSEWHEEL, &AtlasCanvas::OnMouseWheel, this);
}

AtlasCanvas::~AtlasCanvas()
{
	delete glContext;
}

void AtlasCanvas::InitGraphics()
{
	if (glewInit() != GLEW_OK) return;

	query = std::make_unique<AtlasQuery>();

	render = std::make_unique<AtlasRenderSky>();

	auto stars = std::make_unique<AtlasRenderStars>(*query);
	auto horizon = std::make_unique<AtlasRenderHorizon>();

	render->AddLayer(std::move(stars));
	render->AddLayer(std::move(horizon));

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