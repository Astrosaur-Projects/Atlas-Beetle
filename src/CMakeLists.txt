add_subdirectory(AtlasUtilities)

add_executable(PlanetariumSoftware WIN32)

target_sources(PlanetariumSoftware PRIVATE
	"AtlasApp.cpp"
	"AtlasGUI/AtlasCanvas/AtlasCanvas.cpp"
	"AtlasGUI/AtlasFrame/AtlasFrame.cpp"
	"AtlasGUI/AtlasMenuBar/AtlasMenuBar.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.cpp"
	"AtlasGUI/AtlasPluginManager/AtlasPluginManager.cpp"
	"AtlasGUI/AtlasCatalogManager/AtlasCatalogManager.cpp"
)

target_include_directories(PlanetariumSoftware PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PlanetariumSoftware PRIVATE
	AtlasUtilities
	wxWidgets::wxWidgets
	OpenGL::GL
)

if(MSVC)
	# Suppress the C28251 warning (inconsistent SAL annotations)
	target_compile_options(PlanetariumSoftware PRIVATE /wd28251)
endif()