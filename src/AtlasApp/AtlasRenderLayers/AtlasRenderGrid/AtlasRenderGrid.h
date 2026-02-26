#ifndef ATLAS_RENDER_GRID_H
#define ATLAS_RENDER_GRID_H

#include "AtlasCore/AtlasGraphics/AtlasRenderLayerInterface.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include <GL/glew.h>

class AtlasRenderGrid : public AtlasRenderLayerInterface
{
public:
    AtlasRenderGrid();
    ~AtlasRenderGrid();

    void Initialize() override;
    void Render(const AtlasCamera& camera) override;

private:
    void BuildGrid();

private:
    GLuint shader;
    GLuint vao, vbo;
    GLint uViewProj;
    GLint uColor;
    
    glm::vec4 color = glm::vec4(0.0f, 0.0f, 1.0f, 0.1f);

    int numOfVertices = 0;

    const int VERTICAL_MARKS = 36;
    const int HORIZONTAL_MARKS = 18;

    const char* HORIZON_VERTEX_SHADER = R"(
        #version 330 core

        layout(location = 0) in vec3 aPosition;

        uniform mat4 uViewProj;

        void main()
        {
            gl_Position = uViewProj * vec4(aPosition, 1.0);
        }
    )";

    const char* HORIZON_FRAGMENT_SHADER = R"(
        #version 330 core

        uniform vec4 uColor;

        out vec4 FragColor;

        void main()
        {
            FragColor = uColor;
        }
    )";
};

#endif