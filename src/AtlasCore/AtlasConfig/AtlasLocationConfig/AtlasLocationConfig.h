#ifndef ATLAS_LOCATION_CONFIG_H
#define ATLAS_LOCATION_CONFIG_H

#include <expected>
#include <shared_mutex>
#include <string>

class AtlasLocationConfig
{
public:
	static AtlasLocationConfig& GetInstance();

	AtlasLocationConfig(AtlasLocationConfig const&) = delete;
	void operator = (AtlasLocationConfig const&) = delete;

public:
	float GetLatitude() const;
	float GetLongitude() const;
	float GetElevation() const;

	std::string GetTimezone() const;

	std::expected<bool, std::string> SetLatitude(float latitude);
	std::expected<bool, std::string> SetLongitude(float longitude);
	std::expected<bool, std::string> SetElevation(float elevation);

	std::expected<bool, std::string> SetTimezone(std::string timezone);

private:
	AtlasLocationConfig();

private:
	mutable std::shared_mutex mutex;

	float latitude;
	float longitude;
	float elevation;

	std::string timezone;

	const float LATITUDE_MIN = -90.0f;
	const float LATITUDE_MAX = 90.0f;

	const float LONGITUDE_MIN = -180.0f;
	const float LONGITUDE_MAX = 180.0f;

	const float ELEVATION_MIN = -500.0f;
	const float ELEVATION_MAX = 9000.0f;
};

#endif
