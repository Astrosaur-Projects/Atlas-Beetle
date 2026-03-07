#ifndef ATLAS_QUERY_VISIBLE_STAR_RENDER_DATA_H
#define ATLAS_QUERY_VISIBLE_STAR_RENDER_DATA_H

#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <glm/ext/vector_float3.hpp>
#include <string>
#include <vector>

class AtlasQueryVisibleStarRenderData
{
public:
    AtlasQueryVisibleStarRenderData();

    std::expected<std::vector<AtlasStar>, std::string> Query(const glm::vec3& forward, float fovDegrees);

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