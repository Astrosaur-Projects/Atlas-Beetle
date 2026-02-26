#include "AtlasCore/AtlasConfig/AtlasConfig.h"

AtlasConfig& AtlasConfig::GetInstance()
{
	static AtlasConfig instance;

	return instance;
}