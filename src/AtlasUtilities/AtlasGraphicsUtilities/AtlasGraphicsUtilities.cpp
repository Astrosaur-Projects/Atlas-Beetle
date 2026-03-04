#include "AtlasUtilities/AtlasGraphicsUtilities/AtlasGraphicsUtilities.h"
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string AtlasGraphicsUtilities::LoadTextFileIntoStringBuffer(std::string path)
{
	std::ifstream file(path);

	if (!file.is_open()) {
		std::string error = std::format("Failed opening file {}", path);
		throw std::runtime_error(error);
	}

	std::stringstream buffer;

	buffer << file.rdbuf();

	return buffer.str();
}