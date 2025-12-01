add_subdirectory(AtlasUtilities)

add_subdirectory(AtlasGUI)

add_executable(PlanetariumSoftware WIN32)

target_sources(PlanetariumSoftware PRIVATE
	"AtlasApp.cpp"
	"AtlasCore/AtlasStartupTasks/AtlasLoadCurl/AtlasLoadCurl.cpp"
	"AtlasCore/AtlasStartupTasks/AtlasCreateDatabase/AtlasCreateDatabase.cpp"
	"AtlasCore/AtlasStartupTasks/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.cpp"
)

target_include_directories(PlanetariumSoftware PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PlanetariumSoftware PRIVATE
	AtlasUtilities
	AtlasGUI
	wxWidgets::wxWidgets
	OpenGL::GL
	CURL::libcurl
	SQLite::SQLite3
)

if(MSVC)
	# Suppress the C28251 warning (inconsistent SAL annotations)
	target_compile_options(PlanetariumSoftware PRIVATE /wd28251)
endif()