#include "AtlasDownloadUtilities.h"
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <expected>
#include <filesystem>
#include <string>
#include <format>

std::expected<CURLcode, std::string> AtlasDownloadUtilities::download(const std::string url, const std::string filename)
{
	CURL* curl = curl_easy_init();

	CURLcode result = CURLE_FAILED_INIT;

	if (!curl) {
		std::string errorMessage = std::format("Error initializing curl: {} (Code: {})", curl_easy_strerror(result), static_cast<int>(result));

		return std::unexpected<std::string>(errorMessage);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AtlasDownloadUtilities::writeDataCallback);

	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	FILE* file = fopen(filename.c_str(), "wb");

	if (!file) {
		result = CURLE_WRITE_ERROR;

		std::string errorMessage = std::format("Error opening file {}: {} (Code: {})", filename.c_str(), curl_easy_strerror(result), static_cast<int>(result));

		return std::unexpected<std::string>(errorMessage);
	}

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

	result = curl_easy_perform(curl);

	fclose(file);

	curl_easy_cleanup(curl);

	if (result) {
		std::string errorMessage = std::format("Error downloading url with curl {}: {} (Code: {})", url.c_str(), curl_easy_strerror(result), static_cast<int>(result));

		return std::unexpected<std::string>(errorMessage);
	}

	return result;
}

size_t AtlasDownloadUtilities::writeDataCallback(void* buffer, size_t size, size_t count, void* stream)
{
	size_t dataWritten = fwrite(buffer, size, count, (FILE*)stream);

	return dataWritten;
}

std::string AtlasDownloadUtilities::getFilenameFromSource(const std::string url)
{
	std::filesystem::path path(url);

	return  path.filename().string();
}