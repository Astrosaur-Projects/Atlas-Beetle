#include "AtlasApp/AtlasRenderLayers/AtlasRenderStars/AtlasRenderStars.h"
#include <AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h>
#include <AtlasCore/AtlasGraphics/AtlasQueryObjects/AtlasFetchStars/AtlasFetchStars.h>
#include <AtlasCore/AtlasObjects/AtlasStar.h>
#include <GL/glew.h>
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

AtlasRenderStars::AtlasRenderStars(AtlasFetchStars& query) : query(query), shader(0), vao(0), vbo(0), uViewProj(-1) { }

AtlasRenderStars::~AtlasRenderStars()
{
	if (vao) { glDeleteVertexArrays(1, &vao); }
	if (vbo) { glDeleteBuffers(1, &vbo); }
	if (shader) { glDeleteProgram(shader); }
}

void AtlasRenderStars::Initialize()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &STAR_VERTEX_SHADER, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &STAR_FRAGMENT_SHADER, nullptr);
	glCompileShader(fragmentShader);

	shader = glCreateProgram();
	glAttachShader(shader, vertexShader);
	glAttachShader(shader, fragmentShader);
	glLinkProgram(shader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	uViewProj = glGetUniformLocation(shader, "uViewProj");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AtlasStar), (void*)offsetof(AtlasStar, x));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(AtlasStar), (void*)offsetof(AtlasStar, mag));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(AtlasStar), (void*)offsetof(AtlasStar, color));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void AtlasRenderStars::Render(const AtlasCamera& camera)
{
	glUseProgram(shader);

	glEnable(GL_PROGRAM_POINT_SIZE);

	glm::mat4 viewProj = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	glUniformMatrix4fv(uViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));

	std::vector<AtlasStar> stars = query.Query(camera.GetForwardVector(), camera.GetFOV());

	if (!stars.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, stars.size() * sizeof(AtlasStar), stars.data(), GL_DYNAMIC_DRAW);

		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, (GLsizei)stars.size());

		glBindVertexArray(0);
	}

	glUseProgram(0);
}