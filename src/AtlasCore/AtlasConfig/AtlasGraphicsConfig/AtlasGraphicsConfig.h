#ifndef ATLAS_GRAPHICS_CONFIG_H
#define ATLAS_GRAPHICS_CONFIG_H

#include "AtlasApp/AtlasQueryObjects/AtlasQueryGraphicsConfig/AtlasQueryGraphicsConfig.h"
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
	float GetMagnitudeLimit() const;

	std::expected<bool, std::string> SetStarPointSize(float size);
	std::expected<bool, std::string> SetMagnitudeLimit(float limit);

	std::expected<bool, std::string> LoadFromDatabase();
	std::expected<bool, std::string> SaveToDatabase();

private:
	AtlasGraphicsConfig();

private:
	std::unique_ptr<AtlasQueryGraphicsConfig> graphicsConfigQueryObject;

	mutable std::shared_mutex mutex;

	float pointSize;
	float magnitudeLimit;

	const float STAR_POINT_SIZE_MIN = 0.0f;
	const float STAR_POINT_SIZE_MAX = 100.0f;

	const float MAGNITUDE_LIMIT_MIN = -27.0f;
	const float MAGNITUDE_LIMIT_MAX = 32.0f;
};

#endif
