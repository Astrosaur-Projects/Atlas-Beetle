#include "AtlasCore/AtlasConfig/AtlasLocationConfig/AtlasLocationConfig.h"
#include <chrono>
#include <expected>
#include <format>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <tuple>

AtlasLocationConfig& AtlasLocationConfig::GetInstance()
{
	static AtlasLocationConfig instance;

	return instance;
}

AtlasLocationConfig::AtlasLocationConfig() { }

float AtlasLocationConfig::GetLatitude() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return latitude;
}

float AtlasLocationConfig::GetLongitude() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return longitude;
}

float AtlasLocationConfig::GetElevation() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return elevation;
}

std::string AtlasLocationConfig::GetTimezone() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return timezone;
}

std::expected<bool, std::string> AtlasLocationConfig::SetLatitude(float lat)
{
	if (lat < LATITUDE_MIN || lat > LATITUDE_MAX) {
		std::string error = std::format("Latitude must be between {} and {}", LATITUDE_MIN, LATITUDE_MAX);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		latitude = lat;
	}

	return true;
}

std::expected<bool, std::string> AtlasLocationConfig::SetLongitude(float lon)
{
	if (lon < LONGITUDE_MIN || lon > LONGITUDE_MAX) {
		std::string error = std::format("Longitude must be between {} and {}", LONGITUDE_MIN, LONGITUDE_MAX);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		longitude = lon;
	}

	return true;
}

std::expected<bool, std::string> AtlasLocationConfig::SetElevation(float elev)
{
	if (elev < ELEVATION_MIN || elev > ELEVATION_MAX) {
		std::string error = std::format("Elevation must be between {} and {}", ELEVATION_MIN, ELEVATION_MAX);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		elevation = elev;
	}

	return true;
}

std::expected<bool, std::string> AtlasLocationConfig::SetTimezone(std::string timezone)
{
	try {
		std::ignore = std::chrono::locate_zone(timezone);
	} catch (...) {
		std::string error = std::format("Timezone {} not found in the IANA Timezone Database", timezone);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		AtlasLocationConfig::timezone = timezone;
	}

	return true;
}