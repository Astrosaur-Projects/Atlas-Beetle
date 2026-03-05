#version 330 core

in vec3 vStarColor;

out vec4 oFragColor;

float getStarAlpha(vec2 pointCoord);

void main()
{
    float alpha = getStarAlpha(gl_PointCoord);
    
    if (alpha <= 0.0) {
        discard;
    }
    
    oFragColor = vec4(vStarColor, alpha);
}