#include "AtlasApp/AtlasRenderLayers/AtlasRenderGrid/AtlasRenderGrid.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasUtilities/AtlasGraphicsUtilities/AtlasGraphicsUtilities.h"
#include <GL/glew.h>
#include <cmath>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <string>
#include <vector>

AtlasRenderGrid::AtlasRenderGrid() : program(0), vao(0), vbo(0), uViewProj(-1), uColor(-1)
{
	vShaderSource = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasGridShaders/Grid.vert");
	fShaderSource = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasGridShaders/Grid.frag");
}

AtlasRenderGrid::~AtlasRenderGrid()
{
	if (vao) { glDeleteVertexArrays(1, &vao); }
	if (vbo) { glDeleteBuffers(1, &vbo); }
	if (program) { glDeleteProgram(program); }
}

void AtlasRenderGrid::Initialize()
{
	GLuint vShader = InitializeShader(GL_VERTEX_SHADER, vShaderSource);
	GLuint fShader = InitializeShader(GL_FRAGMENT_SHADER, fShaderSource);

	program = InitializeProgram(vShader, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	uViewProj = glGetUniformLocation(program, "uViewProj");
	uColor = glGetUniformLocation(program, "uColor");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	AtlasRenderGrid::BuildGrid();
}

GLuint AtlasRenderGrid::InitializeShader(GLenum glShader, std::string source) const
{
	GLuint shader = glCreateShader(glShader);

	const GLchar* cSource = source.c_str();

	glShaderSource(shader, 1, &cSource, nullptr);
	glCompileShader(shader);

	return shader;
}

GLuint AtlasRenderGrid::InitializeProgram(GLuint vShader, GLuint fShader) const
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	return program;
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

	numOfVertices = vertices.size() / 3;
}

void AtlasRenderGrid::Render(const AtlasCamera& camera)
{
	glUseProgram(program);

	glm::mat4 viewProj = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	glUniformMatrix4fv(uViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));

	glUniform4fv(uColor, 1, glm::value_ptr(color));

	glBindVertexArray(vao);

	glDrawArrays(GL_LINES, 0, numOfVertices);

	glBindVertexArray(0);

	glUseProgram(0);
}
