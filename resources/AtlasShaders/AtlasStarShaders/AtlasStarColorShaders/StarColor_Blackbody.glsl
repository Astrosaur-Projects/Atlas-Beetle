float getStarTemperatureKelvin(float aColorIndex) {
    return 4600.0 * ((1.0/(0.92 * aColorIndex + 1.7)) + (1.0 / (0.92 * aColorIndex + 0.62)));
}

vec3 getStarColor(float aColorIndex) {
    float temperature = getStarTemperatureKelvin(aColorIndex);
    float x = 0.0;
    float y = 0.0;

    if (temperature >= 1667.0 && temperature <= 4000.0) {
        x = (-0.2661239 * (1e9 / (temperature * temperature * temperature))) - (0.2343589 * (1e6 / (temperature * temperature))) + (0.8776956 * (1e3 / temperature)) + 0.179910;
    } else if (temperature > 4000.0 && temperature <= 25000.0) {
        x = (-3.0258469 * (1e9 / (temperature * temperature * temperature))) + (2.1070379 * (1e6 / (temperature * temperature))) + (0.2226347 * (1e3 / temperature)) + 0.240390;
    }

    if (temperature >= 1667.0 && temperature <= 2222.0) {
        y = (-1.1063814 * x * x * x) - (1.34811010 * x * x) + (2.18555832 * x) - 0.20219683;
    } else if (temperature > 2222.0 && temperature <= 4000.0) {
        y = (-0.9549476 * x * x * x) - (1.37418593 * x * x) + (2.09137015 * x) - 0.16748867;
    } else if (temperature > 4000.0 && temperature <= 25000.0) {
        y = (3.0817580 * x * x * x) - (5.34811010 * x * x) + (3.75112997 * x) - 0.37001483;
    }

    float cieX = 0.0;
    float cieY = 1.0;
    float cieZ = 0.0;

    if (y != 0.0) {
        cieX = (cieY / y) * x;
        cieZ = (cieY / y) * (1.0 - x - y);
    }

    mat3 sRGB = mat3(
         3.2406255, -0.9689307,  0.0557101,
        -1.5732080,  1.8757561, -0.02040211,
        -0.4986286,  0.0415175,  1.0569959
    );

    vec3 color = sRGB * vec3(cieX, cieY, cieZ);
    color = max(color, vec3(0.0));

    vec3 lowerGammaCorrection = color * 12.92;
    vec3 higherGammaCorrection = 1.055 * pow(color, vec3(1.0 / 2.4)) - 0.055;
    vec3 gammaCorrectionMask = step(vec3(0.0031308), color);

    return mix(lowerGammaCorrection, higherGammaCorrection, gammaCorrectionMask);
}