#include "AtlasCore/AtlasMath/AtlasMath.h"
#include <cmath>
#include <numbers>

double AtlasMath::getRaRadians(double raHours, double raMinutes, double raSeconds)
{
	return static_cast<double>((raHours + (raMinutes / 60) + (raSeconds / 3600)) * (std::numbers::pi / 12));
}

double AtlasMath::getDecRadians(int decSign, double decDegrees, double decMinutes, double decSeconds)
{
	return static_cast<double>((decDegrees + (decMinutes / 60) + (decSeconds / 3600)) * (std::numbers::pi / 180) * decSign);
}

float AtlasMath::getForwardX(double ra_rad, double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad) * std::cos(ra_rad));
}

float AtlasMath::getForwardY(double ra_rad, double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad) * std::sin(ra_rad));
}

float AtlasMath::getForwardZ(double dec_rad)
{
	return static_cast<float>(std::sin(dec_rad));
}

float AtlasMath::getUpX(double ra_rad, double dec_rad)
{
	return static_cast<float>(-1 * std::sin(dec_rad) * std::cos(ra_rad));
}

float AtlasMath::getUpY(double ra_rad, double dec_rad)
{
	return static_cast<float>(-1 * std::sin(dec_rad) * std::sin(ra_rad));
}

float AtlasMath::getUpZ(double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad));
}
