#include "AtlasApp/AtlasConfigRepositories/AtlasLocationConfigRepository/AtlasLocationConfigRepository.h"
#include "AtlasApp/AtlasQueryObjects/AtlasQueryLocationConfig/AtlasQueryLocationConfig.h"
#include "AtlasCore/AtlasConfig/AtlasLocationConfig/AtlasLocationConfig.h"
#include <expected>
#include <memory>
#include <string>
#include <vector>

std::expected<bool, std::string> AtlasLocationConfigRepository::Load(AtlasLocationConfig& config)
{
	std::unique_ptr<AtlasQueryLocationConfig> queryObject = std::make_unique<AtlasQueryLocationConfig>();

	std::expected<std::vector<AtlasQueryLocationConfig::LocationConfigRecord>, std::string> queryResult = queryObject->Query();

	if (!queryResult.has_value()) {
		return std::unexpected<std::string>(queryResult.error());
	}

	std::vector<AtlasQueryLocationConfig::LocationConfigRecord> records = queryResult.value();

	if (records.empty()) { return false; }

	AtlasQueryLocationConfig::LocationConfigRecord data = records.front();

	std::expected<bool, std::string> loadLocationConfigResult = true;

	loadLocationConfigResult = loadLocationConfigResult
		.and_then([&](bool) { return config.SetLatitude(data.latitude); })
		.and_then([&](bool) { return config.SetLongitude(data.longitude); })
		.and_then([&](bool) { return config.SetElevation(data.elevation); });

	return loadLocationConfigResult;
}

std::expected<bool, std::string> AtlasLocationConfigRepository::Save(const AtlasLocationConfig& config)
{
	float latitude = config.GetLatitude();
	float longitude = config.GetLongitude();
	float elevation = config.GetElevation();

	std::unique_ptr<AtlasQueryLocationConfig> locationConfigQueryObject = std::make_unique<AtlasQueryLocationConfig>();

	return locationConfigQueryObject->Update(latitude, longitude, elevation);
}