#ifndef ATLAS_DOWNLOAD_UTILS_H
#define ATLAS_DOWNLOAD_UTILS_H

#include <curl/curl.h>
#include <expected>
#include <string>

namespace AtlasDownloadUtilities
{
	std::expected<CURLcode, std::string> download(const std::string url, const std::string filename);
	size_t writeDataCallback(void* buffer, size_t size, size_t count, void* stream);
	std::string getFilenameFromSource(const std::string url);
};

#endif