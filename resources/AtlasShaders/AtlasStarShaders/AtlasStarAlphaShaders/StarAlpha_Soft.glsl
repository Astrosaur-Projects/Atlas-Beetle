float getStarAlpha(vec2 pointCoord) {
    vec2 centeredPointCoordinate = pointCoord - vec2(0.5);

    float distance = length(centeredPointCoordinate);

    if (distance > 0.5) { 
        return 0.0;
    }

    return 1.0 - smoothstep(0.2, 0.5, distance);
}