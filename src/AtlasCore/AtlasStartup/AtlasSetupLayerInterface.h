#ifndef ATLAS_SETUP_LAYER_INTERFACE_H
#define ATLAS_SETUP_LAYER_INTERFACE_H

#include <expected>
#include <string>

class AtlasSetupLayerInterface
{
public:
	virtual ~AtlasSetupLayerInterface() = default;

	virtual void Initialize() = 0;
	virtual std::expected<bool, std::string> Setup() = 0;
};

#endif