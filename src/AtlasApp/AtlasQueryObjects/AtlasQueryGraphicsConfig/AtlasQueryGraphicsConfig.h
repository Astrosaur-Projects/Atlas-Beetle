#ifndef ATLAS_QUERY_GRAPHICS_CONFIG_H
#define ATLAS_QUERY_GRAPHICS_CONFIG_H

#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <string>
#include <vector>

class AtlasQueryGraphicsConfig
{
public:
	AtlasQueryGraphicsConfig();

	struct GraphicsConfigRecord
	{
		int id;

		float pointSize;

		float magnitudeLimit;
	};

public:
	void InitializeDatabase();
	AtlasDatabaseUtilities::MemorySafeStatement InitializeStatement(std::string query);

	std::expected<std::vector<GraphicsConfigRecord>, std::string> Query();

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
	const std::string QUERY_FETCH_GRAPHICS_CONFIG = "SELECT * FROM GraphicsConfig;";
	const std::string QUERY_UPDATE_GRAPHICS_CONFIG = "UPDATE GraphicsConfig SET pointSize = ?, magnitudeLimit = ? WHERE id = 1;";
};

#endif