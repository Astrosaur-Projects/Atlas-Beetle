#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <numbers>

AtlasCamera::AtlasCamera(float width, float height) : position(0.0f, 0.0f, 0.0f), up(0.0f, 0.0f, 1.0f), fov(45.0f)
{
	forward = glm::vec3(1.0f, 0.0f, 0.0f);

	SetAspectRatio(width, height);

	UpdateView();
}

void AtlasCamera::SetDirection(float ra, float dec)
{
	AtlasCamera::ra = ra;
	AtlasCamera::de = dec;

	float fX = static_cast<float>(std::cos(dec) * std::cos(ra));
	float fY = static_cast<float>(std::cos(dec) * std::sin(ra));
	float fZ = static_cast<float>(std::sin(dec));

	forward = glm::normalize(glm::vec3(fX, fY, fZ));

	float uX = static_cast<float>(-1 * std::sin(dec) * std::cos(ra));
	float uY = static_cast<float>(-1 * std::sin(dec) * std::sin(ra));
	float uZ = static_cast<float>(std::cos(dec));

	up = glm::normalize(glm::vec3(uX, uY, uZ));

	UpdateView();
}

void AtlasCamera::SetAspectRatio(float width, float height)
{
	if (height == 0) { height = 1; }

	ratio = width / height;

	UpdateProjection();
}

void AtlasCamera::SetZoom(float fov)
{
	if (fov < 1.0f) { fov = 1.0f; }
	if (fov > 90.0f) { fov = 90.0f; }

	AtlasCamera::fov = fov;

	UpdateProjection();
}

void AtlasCamera::UpdateProjection()
{
	projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
}

void AtlasCamera::UpdateView()
{
	glm::vec3 target = position + forward;

	view = glm::lookAt(position, target, up);
}

void AtlasCamera::Pan(float dRa, float dDe)
{
	ra -= dRa;
	de += dDe;

	constexpr float limit = glm::radians(90.0f);

	if (de > limit) { de = limit; }
	if (de < -limit) { de = -limit; }

	const float normal = 2.0f * std::numbers::pi;

	if (ra < 0.0f) {
		ra += normal;
	} else if (ra > normal) {
		ra -= normal;
	}

	SetDirection(ra, de);
}