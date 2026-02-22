#include "AtlasApp/AtlasRenderLayers/AtlasRenderGrid/AtlasRenderGrid.h"
#include <glm/gtc/type_ptr.hpp>
#include <numbers>

AtlasRenderGrid::AtlasRenderGrid() : shader(0), vao(0), vbo(0), uViewProj(-1), uColor(-1) { }

AtlasRenderGrid::~AtlasRenderGrid()
{
	if (vao) { glDeleteVertexArrays(1, &vao); }
	if (vbo) { glDeleteBuffers(1, &vbo); }
	if (shader) { glDeleteProgram(shader); }
}

void AtlasRenderGrid::Initialize()
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
	uColor = glGetUniformLocation(shader, "uColor");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);;

	AtlasRenderGrid::BuildGrid();
}

void AtlasRenderGrid::BuildGrid()
{
	std::vector<float> vertices;
	for (int i = 0; i < VERTICAL_MARKS; i++) {
		float theta = (float)i * (std::numbers::pi * 2.0f) / (float)VERTICAL_MARKS;

		for (int j = 1; j < HORIZONTAL_MARKS - 1; j++) {
			float phi1 = (float)j * std::numbers::pi / (float)HORIZONTAL_MARKS;
			float phi2 = (float)(j + 1) * std::numbers::pi / (float)HORIZONTAL_MARKS;

			vertices.push_back(std::cos(theta) * std::sin(phi1));
			vertices.push_back(std::sin(theta) * std::sin(phi1));
			vertices.push_back(std::cos(phi1));

			vertices.push_back(std::cos(theta) * std::sin(phi2));
			vertices.push_back(std::sin(theta) * std::sin(phi2));
			vertices.push_back(std::cos(phi2));
		}
	}

	for (int j = 1; j < HORIZONTAL_MARKS; j++) {
		float phi = (float)j * std::numbers::pi / (float)HORIZONTAL_MARKS;

		for (int i = 0; i < VERTICAL_MARKS; i++) {
			float theta1 = (float)i * (std::numbers::pi * 2.0f) / (float)VERTICAL_MARKS;
			float theta2 = (float)(i + 1) * (std::numbers::pi * 2.0f) / (float)VERTICAL_MARKS;

			vertices.push_back(std::cos(theta1) * std::sin(phi));
			vertices.push_back(std::sin(theta1) * std::sin(phi));
			vertices.push_back(std::cos(phi));

			vertices.push_back(std::cos(theta2) * std::sin(phi));
			vertices.push_back(std::sin(theta2) * std::sin(phi));
			vertices.push_back(std::cos(phi));
		}
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	numOfVerticies = vertices.size() / 3;
}

void AtlasRenderGrid::Render(const AtlasCamera& camera)
{
	glUseProgram(shader);

	glm::mat4 viewProj = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	glUniformMatrix4fv(uViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));

	glUniform4fv(uColor, 1, glm::value_ptr(color));

	glBindVertexArray(vao);

	glDrawArrays(GL_LINES, 0, numOfVerticies);

	glBindVertexArray(0);

	glUseProgram(0);
}
