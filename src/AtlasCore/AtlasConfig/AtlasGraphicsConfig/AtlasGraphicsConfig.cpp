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

AtlasGraphicsConfig::AtlasGraphicsConfig() : pointSize(1.0f), magnitudeLimit(6.5f)
{
	graphicsConfigQueryObject = std::make_unique<AtlasQueryGraphicsConfig>();
}

float AtlasGraphicsConfig::GetStarPointSize() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return pointSize;
}

float AtlasGraphicsConfig::GetMagnitudeLimit() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return magnitudeLimit;
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

std::expected<bool, std::string> AtlasGraphicsConfig::SetMagnitudeLimit(float limit)
{
	if (limit < MAGNITUDE_LIMIT_MIN || limit > MAGNITUDE_LIMIT_MAX) {
		std::string error = std::format("Magnitude limit must be between {} and {}", MAGNITUDE_LIMIT_MIN, MAGNITUDE_LIMIT_MAX);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		magnitudeLimit = limit;
	}

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::LoadFromDatabase()
{
	std::expected<std::vector<AtlasQueryGraphicsConfig::GraphicsConfigRecord>, std::string> queryGraphicsConfigResult = graphicsConfigQueryObject->Query();

	if (!queryGraphicsConfigResult.has_value()) {
		return std::unexpected<std::string>(queryGraphicsConfigResult.error());
	}

	std::vector<AtlasQueryGraphicsConfig::GraphicsConfigRecord> queryGraphicsConfigData = queryGraphicsConfigResult.value();

	if (queryGraphicsConfigData.empty()) {
		return false;
	}

	AtlasQueryGraphicsConfig::GraphicsConfigRecord config = queryGraphicsConfigData.front();

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		pointSize = config.pointSize;
		magnitudeLimit = config.magnitudeLimit;
	}

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SaveToDatabase()
{
	float size;
	float limit;

	{
		std::shared_lock<std::shared_mutex> lock(mutex);

		size = pointSize;
		limit = magnitudeLimit;
	}

	return graphicsConfigQueryObject->Update(size, limit);
}