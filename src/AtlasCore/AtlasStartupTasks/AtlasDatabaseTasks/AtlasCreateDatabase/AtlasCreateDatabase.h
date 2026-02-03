#ifndef ATLAS_CREATE_DB_TASK_H
#define ATLAS_CREATE_DB_TASK_H

#include <expected>
#include <string>

namespace AtlasCreateDatabase
{
	std::expected<bool, std::string> initialize();
};

#endif