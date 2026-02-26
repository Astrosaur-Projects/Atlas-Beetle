#ifndef ATLAS_MATH_H
#define ATLAS_MATH_H

namespace AtlasMath
{
	double GetRaRadians(double raHours, double raMinutes, double raSeconds);

	double GetDecRadians(int decSign, double decDegrees, double decMinutes, double decSeconds);

	float GetForwardX(double ra_rad, double dec_rad);

	float GetForwardY(double ra_rad, double dec_rad);

	float GetForwardZ(double dec_rad);

	float GetUpX(double ra_rad, double dec_rad);

	float GetUpY(double ra_rad, double dec_rad);

	float GetUpZ(double dec_rad);
};

#endif