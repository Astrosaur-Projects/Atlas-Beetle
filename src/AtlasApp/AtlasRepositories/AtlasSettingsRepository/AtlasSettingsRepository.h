#ifndef ATLAS_SETTINGS_REPOSITORY_H
#define ATLAS_SETTINGS_REPOSITORY_H

#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <map>
#include <string>

class AtlasSettingsRepository
{
public:
	AtlasSettingsRepository();

	std::expected<std::string, std::string> Get(const std::string& section, const std::string& key);
	std::expected<bool, std::string> Set(const std::string& section, const std::string& key, const std::string& value);
	std::expected<std::map<std::string, std::string>, std::string> GetSection(const std::string& section);
	std::expected<bool, std::string> SetSection(const std::string& section, const std::map<std::string, std::string>& values);

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;

	const std::string QUERY_GET = "SELECT value FROM Settings WHERE section = ? AND key = ?;";
	const std::string QUERY_SET = "INSERT OR REPLACE INTO Settings (section, key, value) VALUES (?, ?, ?);";
	const std::string QUERY_GET_SECTION = "SELECT key, value FROM Settings WHERE section = ?;";
};

#endif
