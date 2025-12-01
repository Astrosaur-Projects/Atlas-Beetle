#include "AtlasLoadCurl.h"
#include <curl/curl.h>
#include <format>

std::expected<bool, std::string> AtlasLoadCurl::load() const
{
    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

    if (result) {
        std::string errorMessage = std::format("Error initializing curl globally: {} (Code: {})", curl_easy_strerror(result), std::to_underlying(result));

        return std::unexpected<std::string>(errorMessage);
    }

    return true;
}
