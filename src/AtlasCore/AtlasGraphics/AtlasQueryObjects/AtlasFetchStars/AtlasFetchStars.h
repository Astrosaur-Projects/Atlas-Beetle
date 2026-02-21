#ifndef ATLAS_FETCH_STARS_H
#define ATLAS_FETCH_STARS_H

#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <glm/ext/vector_float3.hpp>
#include <string>
#include <vector>

class AtlasFetchStars
{
public:
	AtlasFetchStars();

	std::vector<AtlasStar> Query(const glm::vec3& forward, float fovDegrees);

private:
	AtlasDatabaseUtilities::MemorySafeDatabase database;
	AtlasDatabaseUtilities::MemorySafeStatement statement;

private:
	const std::string QUERY_STAR_RENDER_DATA = R"(
        SELECT 
            StarRenderData.*,
            StarIndex.minX, StarIndex.minY, StarIndex.minZ
        FROM StarIndex
            JOIN StarRenderData ON StarIndex.id = StarRenderData.id
        WHERE StarIndex.minX >= ? AND StarIndex.maxX <= ?
            AND StarIndex.minY >= ? AND StarIndex.maxY <= ?
            AND StarIndex.minZ >= ? AND StarIndex.maxZ <= ?;
    )";
};

#endif