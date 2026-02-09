#ifndef ATLAS_PROJECTION_MATH_H
#define ATLAS_PROJECTION_MATH_H

namespace AtlasProjectionMath
{
	double getRaRadians(double raHours, double raMinutes, double raSeconds);
	double getDecRadians(double decDegrees, double decMinutes, double decSeconds);
	float getCartesianX(double ra_rad, double dec_rad);
	float getCartesianY(double ra_rad, double dec_rad);
	float getCartesianZ(double dec_rad);
};

#endif