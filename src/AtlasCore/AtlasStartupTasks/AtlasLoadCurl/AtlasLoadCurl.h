#ifndef ATLAS_LOAD_CURL_TASK_H
#define ATLAS_LOAD_CURL_TASK_H

#include <expected>
#include <string>

class AtlasLoadCurl
{
public:
	std::expected<bool, std::string> load() const;
};

#endif