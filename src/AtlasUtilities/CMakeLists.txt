add_library(AtlasUtilities STATIC)

target_sources(AtlasUtilities PUBLIC
	"AtlasDownloadUtilities/AtlasDownloadUtilities.cpp"
	"AtlasEnumUtilities.h"
)

target_include_directories(AtlasUtilities PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(AtlasUtilities PRIVATE
	CURL::libcurl
)