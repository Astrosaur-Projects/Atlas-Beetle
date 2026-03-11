add_library(AtlasApp STATIC)

add_subdirectory(AtlasStartupLayers)
add_subdirectory(AtlasRenderLayers)
add_subdirectory(AtlasQueryObjects)
add_subdirectory(AtlasRepositories)

target_include_directories(AtlasApp PUBLIC
	$<TARGET_OBJECTS:AtlasStartupLayers>
	$<TARGET_OBJECTS:AtlasRenderLayers>
	$<TARGET_OBJECTS:AtlasQueryObjects>
	$<TARGET_OBJECTS:AtlasRepositories>
)

target_link_libraries(AtlasApp PRIVATE
	AtlasRepositories
	AtlasQueryObjects
	AtlasRenderLayers
	AtlasStartupLayers
)