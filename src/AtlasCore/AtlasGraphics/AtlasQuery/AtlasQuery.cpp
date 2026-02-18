#include "AtlasCore/AtlasGraphics/AtlasQuery/AtlasQuery.h"
#include <AtlasCore/AtlasObjects/AtlasStar.h>
#include <AtlasUtilities/AtlasDatabaseUtilities/AtlasDatabaseUtilities.h>
#include <expected>
#include <glm/gtc/matrix_transform.hpp>
#include <sqlite3.h>
#include <string>
#include <utility>
#include <vector>

AtlasQuery::AtlasQuery() : database(nullptr), statement(nullptr)
{
	std::expected<AtlasDatabaseUtilities::MemorySafeDatabase, std::string> openDatabaseResult = AtlasDatabaseUtilities::open();

	if (!openDatabaseResult.has_value()) { return; }

	database = std::move(openDatabaseResult.value());

	std::expected<AtlasDatabaseUtilities::MemorySafeStatement, std::string> prepareStatementResult = AtlasDatabaseUtilities::prepareStatement(database.get(), QUERY_STAR_RENDER_DATA);

	if (!prepareStatementResult.has_value()) { return; }

	statement = std::move(prepareStatementResult.value());
}

std::vector<AtlasStar> AtlasQuery::Query(const glm::vec3& forward, float fovDegrees)
{
	float searchRadius = glm::radians(fovDegrees) / 1.5f;

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

	std::expected<std::vector<AtlasStar>, std::string> queryStarRenderDataResult = AtlasDatabaseUtilities::bindStatementParameters(statement.get(), minX, maxX, minY, maxY, minZ, maxZ)
		.and_then([&](bool) { return AtlasDatabaseUtilities::query<AtlasStar>(statement.get(), database.get(), initializeStarFromSQLStatement); });

	if (!queryStarRenderDataResult.has_value()) {
		return std::vector<AtlasStar>();
	}

	return queryStarRenderDataResult.value();
}
