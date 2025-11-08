add_library(AtlasUtilities STATIC)

target_sources(AtlasUtilities PRIVATE
	"AtlasDownloadUtilities/AtlasDownloadUtilities.cpp"
)

target_include_directories(AtlasUtilities PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasEnumUtilities
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasDownloadUtilities
)

target_link_libraries(AtlasUtilities PRIVATE
	CURL::libcurl
)