#ifndef ATLAS_CONFIG_H
#define ATLAS_CONFIG_H

class AtlasConfig
{
public:
	static AtlasConfig& GetInstance();

public:
	AtlasConfig(AtlasConfig const&) = delete;
	void operator = (AtlasConfig const&) = delete;

public:
	bool reset = false;

private:
	AtlasConfig() { }
};

#endif