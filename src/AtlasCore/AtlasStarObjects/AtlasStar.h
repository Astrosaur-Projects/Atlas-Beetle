#ifndef ATLAS_STAR_H
#define ATLAS_STAR_H

struct AtlasStar
{
	int id = 0;

	double ra = 0.0;

	double de = 0.0;

	double pmRa = 0.0;

	double pmDe = 0.0;

	float mag = 0.0f;

	float color = 0.0f;

	struct BoundingBox
	{
		float minX = 0.0f, maxX = 0.0f;

		float minY = 0.0f, maxY = 0.0f;

		float minZ = 0.0f, maxZ = 0.0f;
	} bounds;
};

#endif