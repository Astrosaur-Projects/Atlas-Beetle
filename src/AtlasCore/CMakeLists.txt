add_library(AtlasCore STATIC)

add_subdirectory(AtlasStartupTasks)

target_sources(AtlasCore PRIVATE
	AtlasConfig/AtlasConfig.cpp
	AtlasMath/AtlasProjectionMath/AtlasProjectionMath.cpp
)

target_include_directories(AtlasCore PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasCore PRIVATE
	AtlasUtilities
	AtlasStartupTasks
)