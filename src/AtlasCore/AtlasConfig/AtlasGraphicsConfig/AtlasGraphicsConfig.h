#ifndef ATLAS_GRAPHICS_CONFIG_H
#define ATLAS_GRAPHICS_CONFIG_H

#include <expected>
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

	std::string GetStarPointSizeShader() const;
	std::string GetStarColorShader() const;
	std::string GetStarAlphaShader() const;

	std::expected<bool, std::string> SetStarPointSize(float size);
	std::expected<bool, std::string> SetLowerMagnitudeLimit(float limit);
	std::expected<bool, std::string> SetUpperMagnitudeLimit(float limit);

	std::expected<bool, std::string> SetStarPointSizeShader(std::string path);
	std::expected<bool, std::string> SetStarColorShader(std::string path);
	std::expected<bool, std::string> SetStarAlphaShader(std::string path);

private:
	AtlasGraphicsConfig();

private:
	mutable std::shared_mutex mutex;

	float pointSize = 7.0f;
	float lowerMagnitudeLimit = -27.0f;
	float upperMagnitudeLimit = 32.0f;

	std::string starPointSizeShader = "resources/AtlasShaders/AtlasStarShaders/AtlasStarPointSizeShaders/StarPointSize_Default.glsl";
	std::string starColorShader = "resources/AtlasShaders/AtlasStarShaders/AtlasStarColorShaders/StarColor_Interpolation.glsl";
	std::string starAlphaShader = "resources/AtlasShaders/AtlasStarShaders/AtlasStarAlphaShaders/StarAlpha_Soft.glsl";

	const float STAR_POINT_SIZE_MIN = 0.0f;
	const float STAR_POINT_SIZE_MAX = 10.0f;

	const float MAGNITUDE_LIMIT_MIN = -27.0f;
	const float MAGNITUDE_LIMIT_MAX = 32.0f;
};

#endif