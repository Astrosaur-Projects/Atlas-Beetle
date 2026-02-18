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

	float x = 0.0f, y = 0.0f, z = 0.0f;
};

#endif