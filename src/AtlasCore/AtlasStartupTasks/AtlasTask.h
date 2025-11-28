#ifndef ATLAS_TASK_H
#define ATLAS_TASK_H

#include <string>
#include <expected>

class AtlasTask
{
public:
	virtual ~AtlasTask() {}
	virtual std::expected<bool, std::string> process() const = 0;
};

#endif