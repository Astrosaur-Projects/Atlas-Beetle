#include "AtlasApp/AtlasStartupLayers/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <format>
#include <string>
#include <wx/filefn.h>
#include <wx/filename.h>

std::expected<bool, std::string> AtlasCreateApplicationDirectory::Start()
{
	std::expected<bool, std::string> initDirectoryResult = true;

	initDirectoryResult = initDirectoryResult
		.and_then([&](bool) { return InitDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_DATABASE); })
		.and_then([&](bool) { return InitDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_CATALOGS); })
		.and_then([&](bool) { return InitDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_PLUGINS); });

	return initDirectoryResult;
}

std::expected<bool, std::string> AtlasCreateApplicationDirectory::InitDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory)
{
	std::string path = AtlasDirectoryUtilities::GetDirectoryPath(directory);

	wxFileName fileName = wxFileName::DirName(path);

	if (!fileName.DirExists() && !wxFileName::Mkdir(path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
		std::string error = std::format("Error creating directory: {}", path.c_str());

		return std::unexpected<std::string>(error);
	}

	return true;
}