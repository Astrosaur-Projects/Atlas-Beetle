#include <expected>
#include <string>
#include <sqlite3.h>

class AtlasCreateDatabase
{
public:
	std::expected<bool, std::string> initialize() const;

private:
	std::expected<bool, std::string> initDatabase(sqlite3* &database) const;
	std::expected<bool, std::string> initCatalogDirectoryTable(sqlite3* database) const;
};