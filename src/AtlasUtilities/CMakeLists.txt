add_library(AtlasUtilities INTERFACE)

target_sources(AtlasUtilities PRIVATE
	"AtlasEnumUtilities.h"
)

target_include_directories(AtlasUtilities INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)