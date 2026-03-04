#ifndef ATLAS_RENDER_HORIZON_H
#define ATLAS_RENDER_HORIZON_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayerInterface.h"
#include <GL/glew.h>
#include <string>

class AtlasRenderEquator : public AtlasRenderLayerInterface
{
public:
	AtlasRenderEquator();
	~AtlasRenderEquator();

	void Initialize() override;
	void Render(const AtlasCamera& camera) override;

	GLuint InitializeShader(GLenum shader, std::string source) const;
	GLuint InitializeProgram(GLuint vShader, GLuint fShader) const;
	void BuildEquator() const;

private:
	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLint uViewProj;

	std::string vShaderSource;
	std::string fShaderSource;

	const int SEGMENT_COUNT = 360;
};

#endif