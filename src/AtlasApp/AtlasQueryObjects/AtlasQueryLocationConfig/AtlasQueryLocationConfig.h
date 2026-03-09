#ifndef ATLAS_QUERY_LOCATION_CONFIG_H
#define ATLAS_QUERY_LOCATION_CONFIG_H

#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <string>
#include <vector>

class AtlasQueryLocationConfig
{
public:
	AtlasQueryLocationConfig();

	struct LocationConfigRecord
	{
		int id;

		float latitude;

		float longitude;

		float elevation;
	};

public:
	void InitializeDatabase();
	AtlasDatabaseUtilities::MemorySafeStatement InitializeStatement(std::string query);

	std::expected<std::vector<LocationConfigRecord>, std::string> Query();

	template <typename... Args>
	std::expected<bool, std::string> Update(Args&&... args)
	{
		return AtlasDatabaseUtilities::BindStatementParameters(updateStatement.get(), std::forward<Args>(args)...)
			.and_then([&](bool) { return AtlasDatabaseUtilities::Execute(updateStatement.get(), database.get()); });
	}

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;
	AtlasDatabaseUtilities::MemorySafeStatement fetchStatement;
	AtlasDatabaseUtilities::MemorySafeStatement updateStatement;

private:
	const std::string FETCH_LOCATION_CONFIG = "SELECT * FROM LocationConfig;";
	const std::string UPDATE_LOCATION_CONFIG = R"(
		UPDATE LocationConfig
			SET latitude = ?,
			longitude = ?,
			elevation = ?
		WHERE id = 1;
	)";
};

#endif
