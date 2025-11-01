add_subdirectory(AtlasUtilities)

add_executable(PlanetariumSoftware WIN32)

target_sources(PlanetariumSoftware PRIVATE
	"AtlasApp.cpp"
	"AtlasGUI/AtlasFrame/AtlasFrame.cpp"
	"AtlasGUI/AtlasFrame/AtlasFrame.h"
	"AtlasGUI/AtlasMenuBar/AtlasMenuBar.cpp"
	"AtlasGUI/AtlasMenuBar/AtlasMenuBar.h"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuOptionEnums.h"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.h"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.h"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.cpp"
	"AtlasGUI/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.h"
	"AtlasGUI/AtlasPluginManager/AtlasPluginManager.cpp"
	"AtlasGUI/AtlasPluginManager/AtlasPluginManager.h"
	"AtlasGUI/AtlasCanvas/AtlasCanvas.cpp"
	"AtlasGUI/AtlasCanvas/AtlasCanvas.h"
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