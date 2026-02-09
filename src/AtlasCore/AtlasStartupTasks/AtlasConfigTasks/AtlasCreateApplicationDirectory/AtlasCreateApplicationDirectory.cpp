#include "AtlasCore/AtlasStartupTasks/AtlasConfigTasks/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.h"
#include "AtlasUtilities/AtlasDirectoryUtilities/AtlasDirectoryUtilities.h"
#include <expected>
#include <format>
#include <string>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/string.h>

std::expected<bool, std::string> AtlasCreateApplicationDirectory::initialize()
{
	std::expected<bool, std::string> initDirectoryResult = true;

	initDirectoryResult = initDirectoryResult
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateApplicationDirectory::initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_DATABASE); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateApplicationDirectory::initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_CATALOGS); })
		.and_then([&](bool success) -> std::expected<bool, std::string> { return AtlasCreateApplicationDirectory::initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_PLUGINS); });

	return initDirectoryResult;
}

std::expected<bool, std::string> AtlasCreateApplicationDirectory::initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory)
{
	wxString path = AtlasDirectoryUtilities::getDirectoryPath(directory);

	wxFileName fileName = wxFileName::DirName(path);

	if (!fileName.DirExists() && !wxFileName::Mkdir(path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
		std::string errorMessage = std::format("Error creating directory: {}", path.ToStdString().c_str());

		return std::unexpected<std::string>(errorMessage);
	}

	return true;
}