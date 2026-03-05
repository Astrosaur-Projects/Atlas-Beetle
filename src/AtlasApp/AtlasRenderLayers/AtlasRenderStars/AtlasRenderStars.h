#ifndef ATLAS_RENDER_STARS_H
#define ATLAS_RENDER_STARS_H

#include "AtlasApp/AtlasQueryObjects/AtlasQueryVisibleStarRenderData/AtlasQueryVisibleStarRenderData.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayerInterface.h"
#include <GL/glew.h>

class AtlasRenderStars : public AtlasRenderLayerInterface
{
public:
	AtlasRenderStars();
	~AtlasRenderStars();

	void Initialize() override;
	void Render(const AtlasCamera& camera) override;

private:
	GLuint InitializeShader(GLenum shader, std::string source) const;
	GLuint InitializeProgram(GLuint vShader, GLuint fShader) const;

private:
    std::unique_ptr<AtlasQueryVisibleStarRenderData> visibleStarRenderDataQueryObject;

	GLuint program;
	GLuint vao;
	GLuint vbo;
	GLint uViewProj;

	std::string vShaderSource;
	std::string fShaderSource;

	std::string vStarColor;
	std::string vStarSize;
	std::string fStarAlpha;
};

#endif