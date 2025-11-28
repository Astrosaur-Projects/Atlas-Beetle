#include "AtlasLoadCurl.h"
#include <curl/curl.h>

std::expected<bool, std::string> AtlasLoadCurl::process() const
{
    CURLcode result = curl_global_init(CURL_GLOBAL_ALL);

    return !result;
}
