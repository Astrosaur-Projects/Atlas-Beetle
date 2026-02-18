#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasMath/AtlasProjectionMath/AtlasProjectionMath.h"
#include <cstdlib>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>

AtlasCamera::AtlasCamera(float width, float height) : position(0.0f, 0.0f, 0.0f), up(0.0f, 0.0f, 1.0f), fov(45.0f)
{
	forward = glm::vec3(1.0f, 0.0f, 0.0f);

	SetAspectRatio(width, height);

	UpdateView();
}

void AtlasCamera::SetDirection(float ra, float dec)
{
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

void AtlasCamera::SetZoom(float fovDegrees)
{
	if (fovDegrees < 1.0f) { fovDegrees = 1.0f; }
	if (fovDegrees > 120.0f) { fovDegrees = 120.0f; }

	fov = fovDegrees;

	UpdateProjection();
}

void AtlasCamera::UpdateProjection()
{
	projection = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
}

void AtlasCamera::UpdateView()
{
	glm::vec3 target = position + forward;

	if (std::abs(forward.z) > 0.99f) {
		view = glm::lookAt(position, target, glm::vec3(1.0f, 0.0f, 0.0f));
	} else {
		view = glm::lookAt(position, target, up);
	}
}