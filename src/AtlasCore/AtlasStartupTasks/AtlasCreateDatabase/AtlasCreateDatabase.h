#include "AtlasCore/AtlasStartupTasks/AtlasTask.h"
#include <sqlite3.h>

class AtlasCreateDatabase : public AtlasTask
{
public:
	virtual std::expected<bool, std::string> process() const override;

private:
	virtual std::expected<bool, std::string> initCatalogDirectoryTable(sqlite3* atlasDatabase) const;
};