#include "AtlasApp/AtlasRenderLayers/AtlasRenderEquator/AtlasRenderEquator.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasUtilities/AtlasGraphicsUtilities/AtlasGraphicsUtilities.h"
#include <GL/glew.h>
#include <cmath>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numbers>
#include <vector>

AtlasRenderEquator::AtlasRenderEquator() : program(0), vao(0), vbo(0), uViewProj(-1)
{
	vShaderSource = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasEquatorShaders/Equator.vert");
	fShaderSource = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasEquatorShaders/Equator.frag");
}

AtlasRenderEquator::~AtlasRenderEquator()
{
	if (vao) { glDeleteVertexArrays(1, &vao); }
	if (vbo) { glDeleteBuffers(1, &vbo); }
	if (program) { glDeleteProgram(program); }
}

void AtlasRenderEquator::Initialize()
{
	GLuint vShader = InitializeShader(GL_VERTEX_SHADER, vShaderSource);
	GLuint fShader = InitializeShader(GL_FRAGMENT_SHADER, fShaderSource);

	program = InitializeProgram(vShader, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	uViewProj = glGetUniformLocation(program, "uViewProj");

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	BuildEquator();
}

GLuint AtlasRenderEquator::InitializeShader(GLenum glShader, std::string source) const
{
	GLuint shader = glCreateShader(glShader);

	const GLchar* cSource = source.c_str();

	glShaderSource(shader, 1, &cSource, nullptr);
	glCompileShader(shader);

	return shader;
}

GLuint AtlasRenderEquator::InitializeProgram(GLuint vShader, GLuint fShader) const
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	return program;
}

void AtlasRenderEquator::BuildEquator() const
{
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

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void AtlasRenderEquator::Render(const AtlasCamera& camera)
{
	glUseProgram(program);

	glm::mat4 viewProj = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	glUniformMatrix4fv(uViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));

	glBindVertexArray(vao);

	glDrawArrays(GL_LINE_LOOP, 0, SEGMENT_COUNT);
	glBindVertexArray(0);

	glUseProgram(0);
}