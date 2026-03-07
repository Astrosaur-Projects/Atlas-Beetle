#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in float aMagnitude;
layout(location = 2) in float aColorIndex;

uniform mat4 uViewProj; 
uniform vec3 uStarColor;

out vec3 vStarColor;

vec3 getStarColor(float aColorIndex);

float getStarPointSize(float aMagnitude);

void main()
{
    gl_Position = uViewProj * vec4(aPosition, 1.0);
    gl_PointSize = getStarPointSize(aMagnitude);

    vStarColor = getStarColor(aColorIndex);
}