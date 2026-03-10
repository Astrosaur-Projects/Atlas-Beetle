#include "AtlasApp/AtlasConfigRepositories/AtlasGraphicsConfigRepository/AtlasGraphicsConfigRepository.h"
#include "AtlasApp/AtlasQueryObjects/AtlasQueryGraphicsConfig/AtlasQueryGraphicsConfig.h"
#include "AtlasCore/AtlasConfig/AtlasGraphicsConfig/AtlasGraphicsConfig.h"
#include <expected>
#include <memory>
#include <string>
#include <vector>

std::expected<bool, std::string> AtlasGraphicsConfigRepository::Load(AtlasGraphicsConfig& config)
{
	std::unique_ptr<AtlasQueryGraphicsConfig> graphicsConfigQueryObject = std::make_unique<AtlasQueryGraphicsConfig>();

	std::expected<std::vector<AtlasQueryGraphicsConfig::GraphicsConfigRecord>, std::string> queryGraphicsConfigResult = graphicsConfigQueryObject->Query();

	if (!queryGraphicsConfigResult.has_value()) {
		return std::unexpected<std::string>(queryGraphicsConfigResult.error());
	}

	std::vector<AtlasQueryGraphicsConfig::GraphicsConfigRecord> queryGraphicsConfigData = queryGraphicsConfigResult.value();

	if (queryGraphicsConfigData.empty()) { return false; }

	AtlasQueryGraphicsConfig::GraphicsConfigRecord data = queryGraphicsConfigData.front();

	std::expected<bool, std::string> loadGraphicsConfigResult = true;

	loadGraphicsConfigResult = loadGraphicsConfigResult
		.and_then([&](bool) { return config.SetStarPointSize(data.pointSize); })
		.and_then([&](bool) { return config.SetLowerMagnitudeLimit(data.lowerMagnitudeLimit); })
		.and_then([&](bool) { return config.SetUpperMagnitudeLimit(data.upperMagnitudeLimit); })
		.and_then([&](bool) { return config.SetStarPointSizeShader(data.starPointSizeShader); })
		.and_then([&](bool) { return config.SetStarColorShader(data.starColorShader); })
		.and_then([&](bool) { return config.SetStarAlphaShader(data.starAlphaShader); });

	return loadGraphicsConfigResult;
}

std::expected<bool, std::string> AtlasGraphicsConfigRepository::Save(const AtlasGraphicsConfig& config)
{
	std::unique_ptr<AtlasQueryGraphicsConfig> graphicsConfigQueryObject = std::make_unique<AtlasQueryGraphicsConfig>();

	return graphicsConfigQueryObject->Update(
		config.GetStarPointSize(),
		config.GetLowerMagnitudeLimit(),
		config.GetUpperMagnitudeLimit(),
		config.GetStarPointSizeShader(),
		config.GetStarColorShader(),
		config.GetStarAlphaShader()
	);
}