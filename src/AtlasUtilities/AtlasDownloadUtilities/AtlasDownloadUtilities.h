#ifndef ATLAS_DOWNLOAD_UTILS_H
#define ATLAS_DOWNLOAD_UTILS_H

#include <curl/curl.h>
#include <string>

namespace AtlasDownloadUtilities
{
	CURLcode download(const std::string url, const std::string filename);
	size_t writeDataCallback(void* buffer, size_t size, size_t count, void* stream);
};

#endif