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
    
        layout(location = 0) in vec3 aPosition;
        layout(location = 1) in float aMagnitude;
        layout(location = 2) in float aColorIndex;

        uniform mat4 uViewProj; 

        out vec3 StarColor;

        float getStarTemperature(float aColorIndex) {
            return 4600.0 * ((1.0/(0.92 * aColorIndex + 1.7)) + (1/(0.92 * aColorIndex + 0.62)));
        }

        float getStarSize(float aMagnitude) {
            float size = 6.0 - aMagnitude;
            if (size < 1.0) { size = 1.0; }

            return size;
        }

        void main()
        {
            gl_Position = uViewProj * vec4(aPosition, 1.0);
        
            gl_PointSize = getStarSize(aMagnitude);

            StarColor = vec3(1.0, 1.0, 1.0);
        }
    )";

    const char* STAR_FRAGMENT_SHADER = R"(
        #version 330 core

        in vec3 StarColor;

        out vec4 FragColor;

        void main()
        {
            vec2 centeredPointCoordinate = gl_PointCoord - vec2(0.5);

            float distance = length(centeredPointCoordinate);

            if (distance > 0.5) { discard; }

            float alpha = 1.0 - smoothstep(0.15, 0.55, distance);

            FragColor = vec4(StarColor, alpha);
        }
    )";
};

#endif