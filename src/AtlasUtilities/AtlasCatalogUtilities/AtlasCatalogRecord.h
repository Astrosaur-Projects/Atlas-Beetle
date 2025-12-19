#ifndef ATLAS_CATALOG_RECORD_H
#define ATLAS_CATALOG_RECORD_H

#include <string>

namespace AtlasCatalogUtilities
{
	struct CatalogRecord
	{
		std::string name;
		std::string source;
		std::string type;
		bool isEnabled;
	};
};

#endif