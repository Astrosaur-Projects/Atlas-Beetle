#include "AtlasConfig.h"

AtlasConfig& AtlasConfig::getInstance()
{
	static AtlasConfig instance;
	return instance;
}