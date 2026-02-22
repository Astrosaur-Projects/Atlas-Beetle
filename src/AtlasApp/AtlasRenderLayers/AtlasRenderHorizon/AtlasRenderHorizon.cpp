#include "AtlasApp/AtlasRenderLayers/AtlasRenderHorizon/AtlasRenderHorizon.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include <GL/glew.h>
#include <cmath>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <vector>

AtlasRenderHorizon::AtlasRenderHorizon() : shader(0), vao(0), vbo(0), uViewProj(-1) { }

AtlasRenderHorizon::~AtlasRenderHorizon()
{
	if (vao) { glDeleteVertexArrays(1, &vao); }
	if (vbo) { glDeleteBuffers(1, &vbo); }
	if (shader) { glDeleteProgram(shader); }
}

void AtlasRenderHorizon::Initialize()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &HORIZON_VERTEX_SHADER, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &HORIZON_FRAGMENT_SHADER, nullptr);
	glCompileShader(fragmentShader);

	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	uViewProj = glGetUniformLocation(shader, "uViewProj");

	std::vector<float> vertices;
	for (int i = 0; i < SEGMENT_COUNT; ++i) {
		float theta = (float)i * (std::numbers::pi * 2.0f) / (float)SEGMENT_COUNT;

		float x = std::cos(theta);
		float y = std::sin(theta);
		float z = 0.0f;

		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void AtlasRenderHorizon::Render(const AtlasCamera& camera)
{
	glUseProgram(shader);

	glm::mat4 viewProj = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	glUniformMatrix4fv(uViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));

	glBindVertexArray(vao);

	glDrawArrays(GL_LINE_LOOP, 0, SEGMENT_COUNT);
	glBindVertexArray(0);

	glUseProgram(0);
}