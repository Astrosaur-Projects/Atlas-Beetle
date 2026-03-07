#include "AtlasApp/AtlasQueryObjects/AtlasQueryVisibleStarRenderData/AtlasQueryVisibleStarRenderData.h"
#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include "AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h"
#include <expected>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <sqlite3.h>
#include <string>
#include <utility>
#include <vector>

AtlasQueryVisibleStarRenderData::AtlasQueryVisibleStarRenderData() : database(nullptr), statement(nullptr)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::Open();

	if (!openDatabaseResult.has_value()) { return; }

	database = std::move(openDatabaseResult.value());

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::PrepareStatement(database.get(), QUERY_STAR_RENDER_DATA);

	if (!prepareStatementResult.has_value()) { return; }

	statement = std::move(prepareStatementResult.value());
}

std::expected<std::vector<AtlasStar>, std::string> AtlasQueryVisibleStarRenderData::Query(const glm::vec3& forward, float fovDegrees)
{
	float searchRadius = glm::radians(fovDegrees);

	float minX = forward.x - searchRadius;
	float maxX = forward.x + searchRadius;
	float minY = forward.y - searchRadius;
	float maxY = forward.y + searchRadius;
	float minZ = forward.z - searchRadius;
	float maxZ = forward.z + searchRadius;

	const auto initializeStarFromSQLStatement = [](sqlite3_stmt* statement) -> AtlasStar {
		return AtlasStar {
			.id = sqlite3_column_int(statement, 0),
			.ra = sqlite3_column_double(statement, 1),
			.de = sqlite3_column_double(statement, 2),
			.pmRa = sqlite3_column_double(statement, 3),
			.pmDe = sqlite3_column_double(statement, 4),
			.mag = (float)sqlite3_column_double(statement, 5),
			.color = (float)sqlite3_column_double(statement, 6),
			.x = (float)sqlite3_column_double(statement, 10),
			.y = (float)sqlite3_column_double(statement, 11),
			.z = (float)sqlite3_column_double(statement, 12)
		};
	};

	return AtlasDatabaseUtilities::BindStatementParameters(statement.get(), minX, maxX, minY, maxY, minZ, maxZ)
		.and_then([&](bool) { return AtlasDatabaseUtilities::Query<AtlasStar>(statement.get(), database.get(), initializeStarFromSQLStatement); });
}
