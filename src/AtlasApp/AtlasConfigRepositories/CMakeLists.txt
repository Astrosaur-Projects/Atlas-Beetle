add_library(AtlasConfigRepositories OBJECT)

target_sources(AtlasConfigRepositories PRIVATE
	AtlasGraphicsConfigRepository/AtlasGraphicsConfigRepository.cpp
	AtlasLocationConfigRepository/AtlasLocationConfigRepository.cpp
)

target_include_directories(AtlasConfigRepositories PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasConfigRepositories PRIVATE
	AtlasUtilities
	SQLite::SQLite3
)