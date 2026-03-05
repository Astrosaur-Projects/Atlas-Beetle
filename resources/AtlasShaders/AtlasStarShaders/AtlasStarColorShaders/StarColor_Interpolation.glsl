/*
 * C++ approximation of RBG from B-V using interpolation
 * Original StackOverflow Post: https://stackoverflow.com/questions/21977786/star-b-v-color-index-to-apparent-rgb-color
 */
vec3 getStarColor(float aColorIndex) {
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