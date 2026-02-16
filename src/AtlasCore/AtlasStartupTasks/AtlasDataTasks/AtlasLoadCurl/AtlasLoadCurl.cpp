#include "AtlasCore/AtlasStartupTasks/AtlasDataTasks/AtlasLoadCurl/AtlasLoadCurl.h"
#include <curl/curl.h>
#include <expected>
#include <format>
#include <string>
#include <utility>

std::expected<bool, std::string> AtlasLoadCurl::load()
{
	CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

	if (result) {
		std::string error = std::format("Error initializing curl globally: {} (Code: {})", curl_easy_strerror(result), std::to_underlying(result));

		return std::unexpected<std::string>(error);
	}

	return true;
}