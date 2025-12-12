#include "AtlasDownloadUtilities.h"
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <string>

CURLcode AtlasDownloadUtilities::download(const std::string url, const std::string filename)
{
	CURL* curl = curl_easy_init();

	CURLcode result = CURLE_FAILED_INIT;

	if (!curl) {
		printf("Error initializing curl: %s (Code: %d)", curl_easy_strerror(result), result);

		return result;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);

	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, AtlasDownloadUtilities::writeDataCallback);

	FILE* file = fopen(filename.c_str(), "wb");

	if (!file) {
		result = CURLE_WRITE_ERROR;

		printf("Error opening file %s: %s (Code: %d)", filename.c_str(), curl_easy_strerror(result), result);

		return result;
	}

	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

	result = curl_easy_perform(curl);

	fclose(file);

	return result;
}

size_t AtlasDownloadUtilities::writeDataCallback(void* buffer, size_t size, size_t count, void* stream)
{
	size_t dataWritten = fwrite(buffer, size, count, (FILE*)stream);

	return dataWritten;
}