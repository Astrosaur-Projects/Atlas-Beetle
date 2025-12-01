add_subdirectory(AtlasUtilities)

add_subdirectory(AtlasCore)

add_subdirectory(AtlasGUI)

add_executable(PlanetariumSoftware WIN32)

target_sources(PlanetariumSoftware PRIVATE
	"AtlasApp.cpp"
)

target_include_directories(PlanetariumSoftware PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PlanetariumSoftware PRIVATE
	AtlasUtilities
	AtlasCore
	AtlasGUI
	wxWidgets::wxWidgets
)

if(MSVC)
	# Suppress the C28251 warning (inconsistent SAL annotations)
	target_compile_options(PlanetariumSoftware PRIVATE /wd28251)
endif()