#ifndef ATLAS_MATH_H
#define ATLAS_MATH_H

namespace AtlasMath
{
	double getRaRadians(double raHours, double raMinutes, double raSeconds);

	double getDecRadians(int decSign, double decDegrees, double decMinutes, double decSeconds);

	float getForwardX(double ra_rad, double dec_rad);

	float getForwardY(double ra_rad, double dec_rad);

	float getForwardZ(double dec_rad);

	float getUpX(double ra_rad, double dec_rad);

	float getUpY(double ra_rad, double dec_rad);

	float getUpZ(double dec_rad);
};

#endif