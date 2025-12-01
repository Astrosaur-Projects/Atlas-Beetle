#include <expected>
#include <string>

class AtlasLoadCurl
{
public:
	std::expected<bool, std::string> load() const;
};