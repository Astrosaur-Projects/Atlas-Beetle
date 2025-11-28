#include "AtlasCore/AtlasStartupTasks/AtlasTask.h"

class AtlasLoadCurl : public AtlasTask
{
public:
	virtual std::expected<bool, std::string> process() const override;
};