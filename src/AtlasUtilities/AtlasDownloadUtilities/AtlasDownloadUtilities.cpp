#include "AtlasUtilities/AtlasDownloadUtilities/AtlasDownloadUtilities.h"
#include <cstdio>
#include <cstdlib>
#include <curl/curl.h>
#include <curl/easy.h>
#include <expected>
#include <format>
#include <string>
#include <string.h>

std::expected<CURLcode, std::string> AtlasDownloadUtilities::Download(const std::string url, const std::string filename)
{
	CURL* curl = curl_easy_init();

	CURLcode result = CURLE_FAILED_INIT;

	if (!curl) {
		std::string error = std::format("Error initializing curl: {} (Code: {})", curl_easy_strerror(result), static_cast<int>(result));

		return std::unexpected<std::string>(error);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AtlasDownloadUtilities::WriteDataCallback);

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	FILE* file = fopen(filename.c_str(), "wb");

	if (!file) {
		curl_easy_cleanup(curl);

		std::string error = std::format("Error opening file {}: {}", filename.c_str(), strerror(errno));

		return std::unexpected<std::string>(error);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

	result = curl_easy_perform(curl);

	fclose(file);

	curl_easy_cleanup(curl);

	if (result) {
		std::string error = std::format("Error downloading {}: {} (Code: {})", url.c_str(), curl_easy_strerror(result), static_cast<int>(result));

		return std::unexpected<std::string>(error);
	}

	return result;
}

size_t AtlasDownloadUtilities::WriteDataCallback(void* buffer, size_t size, size_t count, void* stream)
{
	size_t dataWritten = fwrite(buffer, size, count, (FILE*)stream);

	return dataWritten;
}