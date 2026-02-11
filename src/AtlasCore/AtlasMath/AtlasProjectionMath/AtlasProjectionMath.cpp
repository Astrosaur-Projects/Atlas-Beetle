#define _USE_MATH_DEFINES

#include "AtlasCore/AtlasMath/AtlasProjectionMath/AtlasProjectionMath.h"
#include <cmath>

double AtlasProjectionMath::getRaRadians(double raHours, double raMinutes, double raSeconds)
{
	return static_cast<double>((raHours + (raMinutes / 60) + (raSeconds / 3600)) * (M_PI / 12));
}

double AtlasProjectionMath::getDecRadians(double decDegrees, double decMinutes, double decSeconds)
{
	return static_cast<double>((decDegrees + (decMinutes / 60) + (decSeconds / 3600)) * (M_PI / 180));
}

float AtlasProjectionMath::getCartesianX(double ra_rad, double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad) * std::cos(ra_rad));
}

float AtlasProjectionMath::getCartesianY(double ra_rad, double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad) * std::sin(ra_rad));
}

float AtlasProjectionMath::getCartesianZ(double dec_rad)
{
	return static_cast<float>(std::sin(dec_rad));
}