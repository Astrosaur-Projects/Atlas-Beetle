add_library(AtlasRenderLayers OBJECT)

target_sources(AtlasRenderLayers PRIVATE
	AtlasRenderGrid/AtlasRenderGrid.cpp
	AtlasRenderHorizon/AtlasRenderHorizon.cpp
	AtlasRenderStars/AtlasRenderStars.cpp
)

target_include_directories(AtlasRenderLayers PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasRenderLayers PRIVATE
	AtlasUtilities
	OpenGL::GL
	GLEW::GLEW
	glm::glm
)