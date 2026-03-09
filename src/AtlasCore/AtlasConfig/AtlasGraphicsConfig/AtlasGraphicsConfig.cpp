#include "AtlasApp/AtlasQueryObjects/AtlasQueryGraphicsConfig/AtlasQueryGraphicsConfig.h"
#include "AtlasCore/AtlasConfig/AtlasGraphicsConfig/AtlasGraphicsConfig.h"
#include <expected>
#include <format>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>

AtlasGraphicsConfig& AtlasGraphicsConfig::GetInstance()
{
	static AtlasGraphicsConfig instance;

	return instance;
}

AtlasGraphicsConfig::AtlasGraphicsConfig() : pointSize(7.0f), lowerMagnitudeLimit(-27.0f), upperMagnitudeLimit(32.0f) { }

float AtlasGraphicsConfig::GetStarPointSize() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return pointSize;
}

float AtlasGraphicsConfig::GetLowerMagnitudeLimit() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return lowerMagnitudeLimit;
}

float AtlasGraphicsConfig::GetUpperMagnitudeLimit() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return upperMagnitudeLimit;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetStarPointSize(float size)
{
	if (size < STAR_POINT_SIZE_MIN || size > STAR_POINT_SIZE_MAX) {
		std::string error = std::format("Star point size must be between {} and {}", STAR_POINT_SIZE_MIN, STAR_POINT_SIZE_MAX);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		pointSize = size;
	}

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetLowerMagnitudeLimit(float limit)
{
	if (limit < MAGNITUDE_LIMIT_MIN || limit > upperMagnitudeLimit) {
		std::string error = std::format("Lower Magnitude limit must be between {} and {}", MAGNITUDE_LIMIT_MIN, upperMagnitudeLimit);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		lowerMagnitudeLimit = limit;
	}

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetUpperMagnitudeLimit(float limit)
{
	if (limit < lowerMagnitudeLimit || limit > MAGNITUDE_LIMIT_MAX) {
		std::string error = std::format("Upper Magnitude limit must be between {} and {}", lowerMagnitudeLimit, MAGNITUDE_LIMIT_MAX);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		upperMagnitudeLimit = limit;
	}

	return true;
}