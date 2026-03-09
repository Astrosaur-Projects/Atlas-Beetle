add_library(AtlasConfig OBJECT)

target_sources(AtlasConfig PRIVATE
	AtlasGraphicsConfig/AtlasGraphicsConfig.cpp
	AtlasLocationConfig/AtlasLocationConfig.cpp
)

target_include_directories(AtlasConfig PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasConfig PRIVATE
	AtlasUtilities
	SQLite::SQLite3
)