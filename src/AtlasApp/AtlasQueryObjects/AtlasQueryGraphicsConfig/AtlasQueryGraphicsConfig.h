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

		float lowerMagnitudeLimit;

		float upperMagnitudeLimit;

		std::string starPointSizeShader;

		std::string starColorShader;

		std::string starAlphaShader;
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
	const std::string QUERY_UPDATE_GRAPHICS_CONFIG = R"(
		UPDATE GraphicsConfig
			SET pointSize = ?,
			lowerMagnitudeLimit = ?,
			upperMagnitudeLimit = ?,
			starPointSizeShader = ?,
			starColorShader = ?,
			starAlphaShader = ?
		WHERE id = 1;
	)";
};

#endif