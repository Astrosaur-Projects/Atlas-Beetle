#include "AtlasApp/AtlasRepositories/AtlasSettingsRepository/AtlasSettingsRepository.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <map>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

AtlasSettingsRepository::AtlasSettingsRepository()
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::Open();

	if (!openDatabaseResult.has_value()) {
		throw std::runtime_error(openDatabaseResult.error());
	}

	database = std::move(openDatabaseResult.value());
}

std::expected<std::string, std::string> AtlasSettingsRepository::Get(const std::string& section, const std::string& key)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), QUERY_GET);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	AtlasDatabaseUtilities::MemorySafeStatement statement = std::move(prepareStatementResult.value());

	const auto initializeValueFromStatement = [](sqlite3_stmt* stmt) -> std::string {
		const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

		return value ? std::string(value) : std::string();
	};

	std::expected<std::vector<std::string>, std::string> getSettingResult = AtlasDatabaseUtilities::BindStatementParameters(statement.get(), section, key)
		.and_then([&](bool) { return AtlasDatabaseUtilities::Query<std::string>(statement.get(), database.get(), initializeValueFromStatement); });

	if (!getSettingResult.has_value()) {
		return std::unexpected<std::string>(getSettingResult.error());
	}

	if (getSettingResult.value().empty()) {
		std::string error = std::format("Setting {} not found in section {}", key, section);

		return std::unexpected<std::string>(error);
	}

	return getSettingResult.value().front();
}

std::expected<bool, std::string> AtlasSettingsRepository::Set(const std::string& section, const std::string& key, const std::string& value)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), QUERY_SET);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	AtlasDatabaseUtilities::MemorySafeStatement statement = std::move(prepareStatementResult.value());

	return AtlasDatabaseUtilities::BindStatementParameters(statement.get(), section, key, value)
		.and_then([&](bool) { return AtlasDatabaseUtilities::Execute(statement.get(), database.get()); });
}

std::expected<std::map<std::string, std::string>, std::string> AtlasSettingsRepository::GetSection(const std::string& section)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), QUERY_GET_SECTION);

	if (!prepareStatementResult.has_value()) {
		return std::unexpected<std::string>(prepareStatementResult.error());
	}

	AtlasDatabaseUtilities::MemorySafeStatement statement = std::move(prepareStatementResult.value());

	const auto initializeKeyValueFromStatement = [](sqlite3_stmt* stmt) -> std::pair<std::string, std::string> {
		const char* key = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

		return {
			key ? std::string(key) : std::string(),
			value ? std::string(value) : std::string()
		};
	};

	std::expected<std::vector<std::pair<std::string, std::string>>, std::string> getSectionResult = AtlasDatabaseUtilities::BindStatementParameters(statement.get(), section)
		.and_then([&](bool) { return AtlasDatabaseUtilities::Query<std::pair<std::string, std::string>>(statement.get(), database.get(), initializeKeyValueFromStatement); });

	if (!getSectionResult.has_value()) {
		return std::unexpected<std::string>(getSectionResult.error());
	}

	std::map<std::string, std::string> settings;

	for (const auto& [key, value] : getSectionResult.value()) {
		settings[key] = value;
	}

	return settings;
}

std::expected<bool, std::string> AtlasSettingsRepository::SetSection(const std::string& section, const std::map<std::string, std::string>& values)
{
	for (const auto& [key, value] : values) {
		std::expected<bool, std::string> setSectionResult = Set(section, key, value);

		if (!setSectionResult.has_value()) { return setSectionResult; }
	}

	return true;
}