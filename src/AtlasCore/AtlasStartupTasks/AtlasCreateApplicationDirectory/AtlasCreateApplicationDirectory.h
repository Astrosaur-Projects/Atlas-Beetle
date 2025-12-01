#include "AtlasDirectoryUtilities.h"
#include <expected>
#include <string>

class AtlasCreateApplicationDirectory
{
public:
	std::expected<bool, std::string> initialize() const;

private:
	std::expected<bool, std::string> initDirectory(AtlasDirectoryUtilities::AtlasDirectoryEnums directory) const;
};