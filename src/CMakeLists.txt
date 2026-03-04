add_subdirectory(AtlasApp)
add_subdirectory(AtlasCore)
add_subdirectory(AtlasGUI)
add_subdirectory(AtlasUtilities)

add_executable(PlanetariumSoftware WIN32)

add_custom_command(
    TARGET PlanetariumSoftware POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:PlanetariumSoftware>/resources
)

target_sources(PlanetariumSoftware PRIVATE
	AtlasApp.cpp
)

target_include_directories(PlanetariumSoftware PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PlanetariumSoftware PRIVATE
	AtlasApp
	AtlasCore
	AtlasGUI
	AtlasUtilities
	wxWidgets::wxWidgets
)

if(MSVC)
	# Suppress the C28251 warning (inconsistent SAL annotations)
	target_compile_options(PlanetariumSoftware PRIVATE /wd28251)
endif()