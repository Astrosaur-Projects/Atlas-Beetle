#include "AtlasCore/AtlasStartupTasks/AtlasTask.h"
#include "AtlasDatabaseUtilities.h"

class AtlasCreateDatabase : public AtlasTask
{
public:
	virtual std::expected<bool, std::string> process();

private:
	virtual std::expected<bool, std::string> initCatalogDirectoryTable(sqlite3* atlasDatabase);
};