add_library(AtlasApp STATIC)

add_subdirectory(AtlasStartupLayers)

target_sources(AtlasApp PRIVATE
	AtlasRenderLayers/AtlasRenderGrid/AtlasRenderGrid.cpp
	AtlasRenderLayers/AtlasRenderHorizon/AtlasRenderHorizon.cpp
	AtlasRenderLayers/AtlasRenderStars/AtlasRenderStars.cpp
)

target_include_directories(AtlasApp PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasApp PRIVATE
	AtlasUtilities
	AtlasStartupLayers
	OpenGL::GL
	GLEW::GLEW
	glm::glm
)