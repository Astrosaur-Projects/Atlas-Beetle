add_library(AtlasUtilities STATIC)

target_sources(AtlasUtilities PRIVATE
	AtlasDirectoryUtilities/AtlasDirectoryUtilities.cpp
	AtlasDatabaseUtilities/AtlasDatabaseUtilities.cpp
	AtlasDownloadUtilities/AtlasDownloadUtilities.cpp
	AtlasCatalogUtilities/AtlasCatalogUtilities.cpp
 )

target_include_directories(AtlasUtilities PUBLIC 
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasUtilities PRIVATE
	CURL::libcurl
)