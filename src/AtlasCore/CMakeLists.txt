add_library(AtlasCore STATIC)

target_sources(AtlasCore PRIVATE
	AtlasConfig/AtlasConfig.cpp
	AtlasGraphics/AtlasCamera/AtlasCamera.cpp
	AtlasGraphics/AtlasQueryObjects/AtlasFetchStars/AtlasFetchStars.cpp
	AtlasGraphics/AtlasRenderSky/AtlasRenderSky.cpp
	AtlasStartup/AtlasSetupApp/AtlasSetupApp.cpp
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