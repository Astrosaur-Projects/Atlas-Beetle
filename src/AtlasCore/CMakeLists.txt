add_library(AtlasCore STATIC)

target_sources(AtlasCore PRIVATE
	
	AtlasGraphics/AtlasCamera/AtlasCamera.cpp
	AtlasGraphics/AtlasRenderSky/AtlasRenderSky.cpp
	AtlasStartup/AtlasStartApplication/AtlasStartApplication.cpp
	AtlasMath/AtlasMath.cpp
)

target_include_directories(AtlasCore PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasCore PRIVATE
	AtlasUtilities
	OpenGL::GL
	GLEW::GLEW
	glm::glm
)