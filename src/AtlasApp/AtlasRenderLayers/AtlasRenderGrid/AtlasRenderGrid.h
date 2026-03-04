#ifndef ATLAS_RENDER_GRID_H
#define ATLAS_RENDER_GRID_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayerInterface.h"
#include <GL/glew.h>
#include <string>

class AtlasRenderGrid : public AtlasRenderLayerInterface
{
public:
    AtlasRenderGrid();
    ~AtlasRenderGrid();

    void Initialize() override;
    void Render(const AtlasCamera& camera) override;

private:
    GLuint InitializeShader(GLenum shader, std::string source) const;
    GLuint InitializeProgram(GLuint vShader, GLuint fShader) const;
    void BuildGrid();

private:
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLint uViewProj;
    GLint uColor;
    
    glm::vec4 color = glm::vec4(0.0f, 0.0f, 1.0f, 0.1f);

    int numOfVertices = 0;

    std::string vShaderSource;
    std::string fShaderSource;

    const int VERTICAL_MARKS = 36;
    const int HORIZONTAL_MARKS = 18;
};

#endif