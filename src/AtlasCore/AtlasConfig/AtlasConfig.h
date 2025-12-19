#ifndef ATLAS_CONFIG_H
#define ATLAS_CONFIG_H

class AtlasConfig
{
public:
	static AtlasConfig& getInstance();

public:
	AtlasConfig(AtlasConfig const&) = delete;
	void operator = (AtlasConfig const&) = delete;

public:
	bool resetCatalogs = false;
	bool resetGui = false;
	bool resetPlugins = false;
	bool resetSettings = false;

private:
	AtlasConfig() { }
};

#endif