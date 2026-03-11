#include "AtlasCore/AtlasConfig/AtlasGraphicsConfig/AtlasGraphicsConfig.h"
#include <expected>
#include <filesystem>
#include <format>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>

AtlasGraphicsConfig& AtlasGraphicsConfig::GetInstance()
{
	static AtlasGraphicsConfig instance;

	return instance;
}

AtlasGraphicsConfig::AtlasGraphicsConfig() { }

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

std::string AtlasGraphicsConfig::GetStarPointSizeShader() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return starPointSizeShader;
}

std::string AtlasGraphicsConfig::GetStarColorShader() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return starColorShader;
}

std::string AtlasGraphicsConfig::GetStarAlphaShader() const
{
	std::shared_lock<std::shared_mutex> lock(mutex);

	return starAlphaShader;
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
	std::lock_guard<std::shared_mutex> lock(mutex);

	if (limit < MAGNITUDE_LIMIT_MIN || limit > upperMagnitudeLimit) {
		std::string error = std::format("Lower Magnitude limit must be between {} and {}", MAGNITUDE_LIMIT_MIN, upperMagnitudeLimit);

		return std::unexpected<std::string>(error);
	}

	lowerMagnitudeLimit = limit;

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetUpperMagnitudeLimit(float limit)
{
	std::lock_guard<std::shared_mutex> lock(mutex);

	if (limit < lowerMagnitudeLimit || limit > MAGNITUDE_LIMIT_MAX) {
		std::string error = std::format("Upper Magnitude limit must be between {} and {}", lowerMagnitudeLimit, MAGNITUDE_LIMIT_MAX);

		return std::unexpected<std::string>(error);
	}

	upperMagnitudeLimit = limit;

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetStarPointSizeShader(std::string path)
{
	if (!std::filesystem::exists(path)) {
		std::string error = std::format("File {} not found", path);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		starPointSizeShader = path;
	}

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetStarColorShader(std::string path)
{
	if (!std::filesystem::exists(path)) {
		std::string error = std::format("File {} not found", path);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		starColorShader = path;
	}

	return true;
}

std::expected<bool, std::string> AtlasGraphicsConfig::SetStarAlphaShader(std::string path)
{
	if (!std::filesystem::exists(path)) {
		std::string error = std::format("File {} not found", path);

		return std::unexpected<std::string>(error);
	}

	{
		std::lock_guard<std::shared_mutex> lock(mutex);

		starAlphaShader = path;
	}

	return true;
}

void AtlasGraphicsConfig::LoadFrom(const std::map<std::string, std::string>& settings)
{
	if (auto it = settings.find("pointSize"); it != settings.end()) {
		SetStarPointSize(std::stof(it->second));
	}

	if (auto it = settings.find("lowerMagnitudeLimit"); it != settings.end()) {
		SetLowerMagnitudeLimit(std::stof(it->second));
	}

	if (auto it = settings.find("upperMagnitudeLimit"); it != settings.end()) {
		SetUpperMagnitudeLimit(std::stof(it->second));
	}

	if (auto it = settings.find("starPointSizeShader"); it != settings.end()) {
		SetStarPointSizeShader(it->second);
	}

	if (auto it = settings.find("starColorShader"); it != settings.end()) {
		SetStarColorShader(it->second);
	}

	if (auto it = settings.find("starAlphaShader"); it != settings.end()) {
		SetStarAlphaShader(it->second);
	}
}

void AtlasGraphicsConfig::SaveTo(std::map<std::string, std::string>& settings) const
{
	settings["pointSize"] = std::to_string(GetStarPointSize());
	settings["lowerMagnitudeLimit"] = std::to_string(GetLowerMagnitudeLimit());
	settings["upperMagnitudeLimit"] = std::to_string(GetUpperMagnitudeLimit());
	settings["starPointSizeShader"] = GetStarPointSizeShader();
	settings["starColorShader"] = GetStarColorShader();
	settings["starAlphaShader"] = GetStarAlphaShader();
}