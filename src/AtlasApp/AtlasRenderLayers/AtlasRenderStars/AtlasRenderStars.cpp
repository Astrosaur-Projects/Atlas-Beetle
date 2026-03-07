#include "AtlasApp/AtlasQueryObjects/AtlasQueryVisibleStarRenderData/AtlasQueryVisibleStarRenderData.h"
#include "AtlasApp/AtlasRenderLayers/AtlasRenderStars/AtlasRenderStars.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasUtilities/AtlasGraphicsUtilities/AtlasGraphicsUtilities.h"
#include <GL/glew.h>
#include <cstddef>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include <vector>

AtlasRenderStars::AtlasRenderStars() : program(0), vao(0), vbo(0), uViewProj(-1), uStarColor(-1)
{
	visibleStarRenderDataQueryObject = std::make_unique<AtlasQueryVisibleStarRenderData>();

	vShaderSource = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasStarShaders/Star.vert");
	fShaderSource = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasStarShaders/Star.frag");

	vStarSize = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasStarShaders/AtlasStarPointSizeShaders/StarPointSize_Default.glsl");
	vStarColor = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasStarShaders/AtlasStarColorShaders/StarColor_Interpolation.glsl");
	fStarAlpha = AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer("resources/AtlasShaders/AtlasStarShaders/AtlasStarAlphaShaders/StarAlpha_Soft.glsl");
}

AtlasRenderStars::~AtlasRenderStars()
{
	if (vao) { glDeleteVertexArrays(1, &vao); }
	if (vbo) { glDeleteBuffers(1, &vbo); }
	if (program) { glDeleteProgram(program); }
}

void AtlasRenderStars::Initialize()
{
	GLuint vShader = InitializeShader(GL_VERTEX_SHADER, vShaderSource + "\n" + vStarColor + "\n" + vStarSize);
	GLuint fShader = InitializeShader(GL_FRAGMENT_SHADER, fShaderSource + "\n" + fStarAlpha);

	program = InitializeProgram(vShader, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	uViewProj = glGetUniformLocation(program, "uViewProj");
	uStarColor = glGetUniformLocation(program, "uStarColor");

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

GLuint AtlasRenderStars::InitializeShader(GLenum glShader, std::string source) const
{
	GLuint shader = glCreateShader(glShader);

	const GLchar* cSource = source.c_str();

	glShaderSource(shader, 1, &cSource, nullptr);
	glCompileShader(shader);

	return shader;
}

GLuint AtlasRenderStars::InitializeProgram(GLuint vShader, GLuint fShader) const
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	glLinkProgram(program);

	return program;
}

void AtlasRenderStars::Render(const AtlasCamera& camera)
{
	glUseProgram(program);

	glEnable(GL_PROGRAM_POINT_SIZE);

	glm::mat4 viewProj = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	glUniformMatrix4fv(uViewProj, 1, GL_FALSE, glm::value_ptr(viewProj));

	glUniform3f(uStarColor, 1.0f, 1.0f, 1.0f);

	std::expected<std::vector<AtlasStar>, std::string> queryVisibleStarRenderDataResult = visibleStarRenderDataQueryObject->Query(camera.GetForwardVector(), camera.GetFOV());

	if (!queryVisibleStarRenderDataResult.has_value()) { return; }

	std::vector<AtlasStar> stars = queryVisibleStarRenderDataResult.value();

	if (!stars.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, stars.size() * sizeof(AtlasStar), stars.data(), GL_DYNAMIC_DRAW);

		glBindVertexArray(vao);
		glDrawArrays(GL_POINTS, 0, (GLsizei)stars.size());

		glBindVertexArray(0);
	}

	glUseProgram(0);
}