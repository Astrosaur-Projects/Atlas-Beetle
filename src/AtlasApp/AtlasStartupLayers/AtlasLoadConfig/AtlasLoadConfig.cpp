#include "AtlasApp/AtlasStartupLayers/AtlasLoadConfig/AtlasLoadConfig.h"
#include "AtlasApp/AtlasRepositories/AtlasSettingsRepository/AtlasSettingsRepository.h"
#include "AtlasCore/AtlasConfig/AtlasGraphicsConfig/AtlasGraphicsConfig.h"
#include "AtlasCore/AtlasConfig/AtlasLocationConfig/AtlasLocationConfig.h"
#include <expected>
#include <map>
#include <string>

std::expected<bool, std::string> AtlasLoadConfig::Start()
{
	AtlasSettingsRepository settingsRepository;

	std::expected<std::map<std::string, std::string>, std::string> graphicsSettings = settingsRepository.GetSection("graphics");

	if (graphicsSettings.has_value()) {
		AtlasGraphicsConfig::GetInstance().LoadFrom(graphicsSettings.value());
	}

	std::expected<std::map<std::string, std::string>, std::string> locationSettings = settingsRepository.GetSection("location");

	if (locationSettings.has_value()) {
		AtlasLocationConfig::GetInstance().LoadFrom(locationSettings.value());
	}

	return true;
}
