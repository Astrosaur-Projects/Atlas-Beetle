#include "AtlasCreateApplicationDirectory.h"
#include "AtlasDirectoryUtilities.h"
#include <format>
#include <wx/filename.h>

std::expected<bool, std::string> AtlasCreateApplicationDirectory::initialize() const
{
    std::expected<bool, std::string> initDirectoryResult = true;

    initDirectoryResult = initDirectoryResult
        .and_then([&](bool success) -> std::expected<bool, std::string> { return initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_DATABASE); })
        .and_then([&](bool success) -> std::expected<bool, std::string> { return initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_CATALOGS); })
        .and_then([&](bool success) -> std::expected<bool, std::string> { return initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums::DIR_PLUGINS); });

    return initDirectoryResult;
}

std::expected<bool, std::string> AtlasCreateApplicationDirectory::initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory) const
{
    wxString path = AtlasDirectoryUtilities::getDirectoryPath(directory);

    wxFileName fileName(path);

    if (!fileName.DirExists() && !wxFileName::Mkdir(path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
        std::string errorMessage = std::format("Error creating directory: {}",path.ToStdString().c_str());

        return std::unexpected<std::string>(errorMessage);
    }

    return true;
}