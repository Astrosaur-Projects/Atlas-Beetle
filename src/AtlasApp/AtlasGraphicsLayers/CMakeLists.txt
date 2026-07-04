add_library(AtlasGraphicsLayers OBJECT)

target_sources(AtlasGraphicsLayers PRIVATE
	AtlasRenderStars/AtlasRenderStars.cpp
)

target_include_directories(AtlasGraphicsLayers PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasGraphicsLayers PRIVATE
	AtlasUtilities
	OpenGL::GL
	GLEW::GLEW
	glm::glm
)