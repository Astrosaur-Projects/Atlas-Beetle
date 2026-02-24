add_library(AtlasApp STATIC)

add_subdirectory(AtlasStartupLayers)
add_subdirectory(AtlasRenderLayers)

target_include_directories(AtlasApp PUBLIC
	$<TARGET_OBJECTS:AtlasStartupLayers>
    $<TARGET_OBJECTS:AtlasRenderLayers>
)

target_link_libraries(AtlasApp PRIVATE
	AtlasStartupLayers
	AtlasRenderLayers
)