add_library(AtlasCore STATIC)

add_subdirectory(AtlasConfig)

target_sources(AtlasCore PRIVATE
	AtlasGraphics/AtlasCamera/AtlasCamera.cpp
	AtlasGraphics/AtlasRenderSky/AtlasRenderSky.cpp
	AtlasStartup/AtlasStartApplication/AtlasStartApplication.cpp
	AtlasMath/AtlasMath.cpp
)

target_include_directories(AtlasCore PUBLIC
	$<TARGET_OBJECTS:AtlasConfig>
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasCore PRIVATE
	AtlasUtilities
	AtlasConfig
	OpenGL::GL
	GLEW::GLEW
	glm::glm
)