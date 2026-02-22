add_library(AtlasCore STATIC)

add_subdirectory(AtlasStartupTasks)

target_sources(AtlasCore PRIVATE
	AtlasConfig/AtlasConfig.cpp
	AtlasGraphics/AtlasCamera/AtlasCamera.cpp
	AtlasGraphics/AtlasQueryObjects/AtlasFetchStars/AtlasFetchStars.cpp
	AtlasGraphics/AtlasRenderSky/AtlasRenderSky.cpp
	AtlasMath/AtlasMath.cpp
)

target_include_directories(AtlasCore PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasCore PRIVATE
	AtlasUtilities
	AtlasStartupTasks
	OpenGL::GL
	GLEW::GLEW
	glm::glm
)