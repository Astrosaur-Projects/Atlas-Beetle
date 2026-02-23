#ifndef ATLAS_CAMERA_H
#define ATLAS_CAMERA_H

#include <GL/glew.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class AtlasCamera
{
public:
	AtlasCamera(float width, float heigth);

	void SetDirection(float ra_rad, float dec_rad);
	void SetAspectRatio(float width, float height);
	void SetZoom(float fov);
	void Pan(float dRa, float dDe);

	const glm::mat4& GetViewMatrix() const { return view; }
	const glm::mat4& GetProjectionMatrix() const { return projection; }

	glm::vec3 GetForwardVector() const { return forward; }

	float GetFOV() const { return fov; }

private:
	void UpdateProjection();
	void UpdateView();

private:
	float fov;
	float ratio;
	float ra = 0.0f;
	float de = 0.0f;

	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;

	glm::mat4 view;
	glm::mat4 projection;
};

#endif