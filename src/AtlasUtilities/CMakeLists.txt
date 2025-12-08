add_library(AtlasUtilities STATIC)

target_sources(AtlasUtilities PRIVATE
	"AtlasDirectoryUtilities/AtlasDirectoryUtilities.cpp"
	"AtlasDownloadUtilities/AtlasDownloadUtilities.cpp"
	"AtlasCatalogUtilities/AtlasCatalogUtilities.cpp"
)

target_include_directories(AtlasUtilities PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasDirectoryUtilities
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasDownloadUtilities
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasCatalogUtilities
)

target_link_libraries(AtlasUtilities PRIVATE
	CURL::libcurl
)