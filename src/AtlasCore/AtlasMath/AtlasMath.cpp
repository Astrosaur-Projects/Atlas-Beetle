#include "AtlasCore/AtlasMath/AtlasMath.h"
#include <cmath>
#include <numbers>

double AtlasMath::GetRaRadians(double raHours, double raMinutes, double raSeconds)
{
	return static_cast<double>((raHours + (raMinutes / 60) + (raSeconds / 3600)) * (std::numbers::pi / 12));
}

double AtlasMath::GetDecRadians(int decSign, double decDegrees, double decMinutes, double decSeconds)
{
	return static_cast<double>((decDegrees + (decMinutes / 60) + (decSeconds / 3600)) * (std::numbers::pi / 180) * decSign);
}

float AtlasMath::GetForwardX(double ra_rad, double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad) * std::cos(ra_rad));
}

float AtlasMath::GetForwardY(double ra_rad, double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad) * std::sin(ra_rad));
}

float AtlasMath::GetForwardZ(double dec_rad)
{
	return static_cast<float>(std::sin(dec_rad));
}

float AtlasMath::GetUpX(double ra_rad, double dec_rad)
{
	return static_cast<float>(-1 * std::sin(dec_rad) * std::cos(ra_rad));
}

float AtlasMath::GetUpY(double ra_rad, double dec_rad)
{
	return static_cast<float>(-1 * std::sin(dec_rad) * std::sin(ra_rad));
}

float AtlasMath::GetUpZ(double dec_rad)
{
	return static_cast<float>(std::cos(dec_rad));
}
