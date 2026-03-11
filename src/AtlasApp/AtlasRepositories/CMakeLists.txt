add_library(AtlasRepositories OBJECT)

target_sources(AtlasRepositories PRIVATE
	AtlasSettingsRepository/AtlasSettingsRepository.cpp
)

target_include_directories(AtlasRepositories PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasRepositories PRIVATE
	AtlasUtilities
	SQLite::SQLite3
)