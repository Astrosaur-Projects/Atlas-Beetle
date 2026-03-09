add_library(AtlasQueryObjects OBJECT)

target_sources(AtlasQueryObjects PRIVATE
	AtlasQueryCatalogDirectory/AtlasQueryCatalogDirectory.cpp
	AtlasQueryGraphicsConfig/AtlasQueryGraphicsConfig.cpp
	AtlasQueryLocationConfig/AtlasQueryLocationConfig.cpp
	AtlasQueryVisibleStarRenderData/AtlasQueryVisibleStarRenderData.cpp
 )

target_include_directories(AtlasQueryObjects PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasQueryObjects PRIVATE
	AtlasUtilities
	SQLite::SQLite3
)