#ifndef ATLAS_GRAPHICS_CONFIG_H
#define ATLAS_GRAPHICS_CONFIG_H

#include <expected>
#include <memory>
#include <shared_mutex>
#include <string>

class AtlasGraphicsConfig
{
public:
	static AtlasGraphicsConfig& GetInstance();

	AtlasGraphicsConfig(AtlasGraphicsConfig const&) = delete;
	void operator = (AtlasGraphicsConfig const&) = delete;

public:
	float GetStarPointSize() const;
	float GetLowerMagnitudeLimit() const;
	float GetUpperMagnitudeLimit() const;

	std::expected<bool, std::string> SetStarPointSize(float size);
	std::expected<bool, std::string> SetLowerMagnitudeLimit(float limit);
	std::expected<bool, std::string> SetUpperMagnitudeLimit(float limit);

private:
	AtlasGraphicsConfig();

private:
	mutable std::shared_mutex mutex;

	float pointSize;
	float lowerMagnitudeLimit;
	float upperMagnitudeLimit;

	const float STAR_POINT_SIZE_MIN = 0.0f;
	const float STAR_POINT_SIZE_MAX = 10.0f;

	const float MAGNITUDE_LIMIT_MIN = -27.0f;
	const float MAGNITUDE_LIMIT_MAX = 32.0f;
};

#endif