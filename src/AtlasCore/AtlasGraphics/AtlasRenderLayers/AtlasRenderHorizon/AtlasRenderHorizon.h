#ifndef ATLAS_RENDER_HORIZON_H
#define ATLAS_RENDER_HORIZON_H

#include "AtlasCore/AtlasGraphics/AtlasRenderLayers/AtlasLayerInterface.h"
#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include <GL/glew.h>

class AtlasRenderHorizon : public AtlasLayerInterface
{
public:
	AtlasRenderHorizon();
	~AtlasRenderHorizon();

	void Initialize() override;
	void Render(const AtlasCamera& camera) override;

private:
	GLuint shader;
	GLuint vao, vbo;
	GLint uViewProj;

	const int SEGMENT_COUNT = 360;

	const char* HORIZON_VERTEX_SHADER = R"(
        #version 330 core

        layout(location = 0) in vec3 aPos;

        uniform mat4 uViewProj;

        void main()
        {
            gl_Position = uViewProj * vec4(aPos, 1.0);
        }
    )";

	const char* HORIZON_FRAGMENT_SHADER = R"(
        #version 330 core

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";
};

#endif