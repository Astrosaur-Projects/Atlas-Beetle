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

	std::expected<std::vector<GraphicsConfigRecord>, std::string> Query();

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;
	AtlasDatabaseUtilities::MemorySafeStatement statement;

private:
	const std::string QUERY_GRAPHICS_CONFIG = "SELECT * FROM GraphicsConfig;";
};

#endif