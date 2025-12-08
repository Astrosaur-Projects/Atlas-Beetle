#ifndef ATLAS_LOAD_CURL_TASK_H
#define ATLAS_LOAD_CURL_TASK_H

#include <expected>
#include <string>

namespace AtlasLoadCurl
{
	std::expected<bool, std::string> load();
};

#endif