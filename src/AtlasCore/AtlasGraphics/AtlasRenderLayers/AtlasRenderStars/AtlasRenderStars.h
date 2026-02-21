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

        /*
         * C++ approximation of RBG from B-V using interpolation
         * Original StackOverflow Post: https://stackoverflow.com/questions/21977786/star-b-v-color-index-to-apparent-rgb-color
         */
        vec3 getStarColorInterpolation(float aColorIndex) {
            float t = 0.0;
            float r = 0.0;
            float g = 0.0;
            float b = 0.0;

            if (aColorIndex < -0.4) { aColorIndex = -0.4; }
            if (aColorIndex > 2.0) { aColorIndex = 2.0; }

            if (aColorIndex >= -0.40 && aColorIndex < 0.00) {
                t = (aColorIndex + 0.40) / (0.00 + 0.40);
                r = 0.61 + (0.11 * t) + (0.1 * t * t);
            } else if (aColorIndex >= 0.00 && aColorIndex < 0.40) {
                t = (aColorIndex - 0.00) / (0.40 - 0.00);
                r = 0.83 + (0.17 * t);
            } else if (aColorIndex >= 0.40 && aColorIndex < 2.10) {
                t = (aColorIndex - 0.40) / (2.10 - 0.40);
                r = 1.00;
            }

            if (aColorIndex >= -0.40 && aColorIndex < 0.00) {
                t = (aColorIndex + 0.40) / (0.00 + 0.40);
                g = 0.70 + (0.07 * t) + (0.1 * t * t);
            } else if (aColorIndex >= 0.00 && aColorIndex < 0.40) {
                t = (aColorIndex - 0.00) / (0.40 - 0.00);
                g = 0.87 + (0.11 * t);
            } else if (aColorIndex >= 0.40 && aColorIndex < 1.60) {
                t = (aColorIndex - 0.40) / (1.60 - 0.40);
                g = 0.98 - (0.16 * t);
            } else if (aColorIndex >= 1.60 && aColorIndex < 2.00) {
                t = (aColorIndex - 1.60) / (2.00 - 1.60);
                g = 0.82 - (0.5 * t * t);
            }

            if (aColorIndex >= -0.40 && aColorIndex < 0.40) {
                t = (aColorIndex + 0.40) / (0.40 + 0.40);
                b = 1.00;
            } else if (aColorIndex >= 0.40 && aColorIndex < 1.50) {
                t = (aColorIndex - 0.40) / (1.50 - 0.40);
                b = 1.00 - (0.47 * t) + (0.1 * t * t);
            } else if (aColorIndex >= 1.50 && aColorIndex < 1.94) {
                t = (aColorIndex - 1.50) / (1.94 - 1.50);
                b = 0.63 - (0.6 * t * t);
            }
            
            return vec3(r, g, b);
        }

        float getStarTemperatureKelvin(float aColorIndex) {
            return 4600.0 * ((1.0/(0.92 * aColorIndex + 1.7)) + (1.0 / (0.92 * aColorIndex + 0.62)));
        }

        vec3 getStarColor(float aColorIndex) {
            float tKelvin = getStarTemperatureKelvin(aColorIndex);
            float cX = 0.0;
            float cY = 0.0;

            if (tKelvin >= 1667.0 && tKelvin <= 4000.0) {
                cX = (-0.2661239 * (1e9 / (tKelvin * tKelvin * tKelvin))) - (0.2343589 * (1e6 / (tKelvin * tKelvin))) + (0.8776956 * (1e3 / tKelvin)) + 0.179910;
            } else if (tKelvin > 4000.0 && tKelvin <= 25000.0) {
                cX = (-3.0258469 * (1e9 / (tKelvin * tKelvin * tKelvin))) + (2.1070379 * (1e6 / (tKelvin * tKelvin))) + (0.2226347 * (1e3 / tKelvin)) + 0.240390;
            }

            if (tKelvin >= 1667.0 && tKelvin <= 2222.0) {
                cY = (-1.1063814 * cX * cX * cX) - (1.34811010 * cX * cX) + (2.18555832 * cX) - 0.20219683;
            } else if (tKelvin > 2222.0 && tKelvin <= 4000.0) {
                cY = (-0.9549476 * cX * cX * cX) - (1.37418593 * cX * cX) + (2.09137015 * cX) - 0.16748867;
            } else if (tKelvin > 4000.0 && tKelvin <= 25000.0) {
                cY = (3.0817580 * cX * cX * cX) - (5.34811010 * cX * cX) + (3.75112997 * cX) - 0.37001483;
            }

            float cieX = 0.0;
            float cieY = 1.0;
            float cieZ = 0.0;

            if (cY != 0.0) {
                cieX = (cieY / cY) * cX;
                cieZ = (cieY / cY) * (1.0 - cX - cY);
            }

            mat3 sRGB = mat3(
                 3.2406255, -0.9689307,  0.0557101,
                -1.5732080,  1.8757561, -0.02040211,
                -0.4986286,  0.0415175,  1.0569959
            );

            vec3 sColor = sRGB * vec3(cieX, cieY, cieZ);

            sColor = max(sColor, vec3(0.0));

            vec3 lowerGammaCorrection = sColor * 12.92;
            vec3 higherGammaCorrection = 1.055 * pow(sColor, vec3(1.0 / 2.4)) - 0.055;

            vec3 gammaCorrectionMask = step(vec3(0.0031308), sColor);

            sColor = mix(lowerGammaCorrection, higherGammaCorrection, gammaCorrectionMask);

            return sColor;
        }

        float getStarPointSize(float aMagnitude) {
            return max(7.0 - aMagnitude, 1.5);
        }

        void main()
        {
            gl_Position = uViewProj * vec4(aPosition, 1.0);
        
            gl_PointSize = getStarPointSize(aMagnitude);

            StarColor = getStarColorInterpolation(aColorIndex);
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

            float alpha = 1.0 - smoothstep(0.2, 0.5, distance);

            FragColor = vec4(StarColor, alpha);
        }
    )";
};

#endif