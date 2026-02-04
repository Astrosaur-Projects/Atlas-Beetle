#ifndef ATLAS_CREATE_STAR_RENDER_DATA_DB_TASK_H
#define ATLAS_CREATE_STAR_RENDER_DATA_DB_TASK_H

#include <expected>
#include <string>
#include <sqlite3.h>

namespace AtlasCreateStarRenderDataTable
{
	std::expected<bool, std::string> create(sqlite3* database);
	std::expected<bool, std::string> initStarRenderData(sqlite3* database);
};

#endif