#ifndef ATLAS_STARTUP_LAYER_INTERFACE_H
#define ATLAS_STARTUP_LAYER_INTERFACE_H

#include <expected>
#include <string>

class AtlasStartupLayerInterface
{
public:
	virtual ~AtlasStartupLayerInterface() = default;

	virtual void Initialize() { };
	virtual std::expected<bool, std::string> Start() { return true; };
};

#endif