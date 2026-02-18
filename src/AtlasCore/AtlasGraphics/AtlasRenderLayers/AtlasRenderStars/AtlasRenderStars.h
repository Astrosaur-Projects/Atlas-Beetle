#ifndef ATLAS_DRAW_STARS_H
#define ATLAS_DRAW_STARS_H

#include "AtlasCore/AtlasGraphics/AtlasCamera/AtlasCamera.h"
#include "AtlasCore/AtlasGraphics/AtlasQuery/AtlasQuery.h"
#include "AtlasCore/AtlasGraphics/AtlasRenderLayers/AtlasLayerInterface.h"
#include <GL/glew.h>

class AtlasRenderStars : public AtlasLayerInterface
{
public:
	AtlasRenderStars(AtlasQuery& query);
	~AtlasRenderStars();

	void Initialize() override;
	void Render(const AtlasCamera& camera) override;

private:
	AtlasQuery& query;

	GLuint shader;
	GLuint vao, vbo;
	GLint uViewProj;

    const char* STAR_VERTEX_SHADER = R"(
        #version 330 core
    
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in float aMag;
        layout(location = 2) in float aColor;

        uniform mat4 uViewProj; 

        void main()
        {
            gl_Position = uViewProj * vec4(aPos, 1.0);

            float size = 6.0 - aMag;
            if (size < 1.0) size = 1.0;
        
            gl_PointSize = size;
        }
    )";

    const char* STAR_FRAGMENT_SHADER = R"(
        #version 330 core

        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0); 
        }
    )";
};

#endif