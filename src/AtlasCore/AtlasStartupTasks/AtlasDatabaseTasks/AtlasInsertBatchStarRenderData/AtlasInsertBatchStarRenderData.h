#ifndef ATLAS_INSERT_BATCH_STAR_RENDER_DATA_TASK_H
#define ATLAS_INSERT_BATCH_STAR_RENDER_DATA_TASK_H

#include "AtlasCore/AtlasObjects/AtlasStar.h"
#include <expected>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace AtlasInsertBatchStarRenderData
{
	std::expected<bool, std::string> insert(sqlite3* database, std::vector<AtlasStar> buffer);

	std::expected<bool, std::string> insertStarRenderData(sqlite3* database, std::vector<AtlasStar> buffer);
};

#endif