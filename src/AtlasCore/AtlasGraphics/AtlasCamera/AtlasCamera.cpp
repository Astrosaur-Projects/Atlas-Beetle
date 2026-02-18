#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasMath/AtlasProjectionMath/AtlasProjectionMath.h"
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

	float x = AtlasProjectionMath::getCartesianX(ra, dec);
	float y = AtlasProjectionMath::getCartesianY(ra, dec);
	float z = AtlasProjectionMath::getCartesianZ(dec);

	forward = glm::normalize(glm::vec3(x, y, z));

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

	const float limit = 1.57f;
	if (de > limit) { de = limit; }
	if (de < -limit) { de = -limit; }

	const float normal = 2.0f * std::numbers::pi_v<float>;

	if (ra < 0.0f) {
		ra += normal;
	} else if (ra > normal) {
		ra -= normal;
	}

	SetDirection(ra, de);
}