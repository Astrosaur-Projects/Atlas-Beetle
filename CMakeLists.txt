# CMakeList.txt : CMake project for Atlas-Beetle
cmake_minimum_required(VERSION 3.27)

project("Atlas-Beetle"
	VERSION 0.0.1
	DESCRIPTION "A home-brewed, planetarium software with plugin extensibility"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS gl core base)

add_executable(PlanetariumSoftware WIN32)

target_sources(PlanetariumSoftware PRIVATE
	"src/AtlasApp.cpp"
	"src/AtlasUtilities/AtlasEnumUtilities.h"
	"src/AtlasGUI/AtlasFrame/AtlasFrame.cpp"
	"src/AtlasGUI/AtlasFrame/AtlasFrame.h"
	"src/AtlasGUI/AtlasMenuBar/AtlasMenuBar.cpp"
	"src/AtlasGUI/AtlasMenuBar/AtlasMenuBar.h"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuOptionEnums.h"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.cpp"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.h"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.cpp"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.cpp"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.h"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.cpp"
	"src/AtlasGUI/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.h"
	"src/AtlasGUI/AtlasPluginManager/AtlasPluginManager.cpp"
	"src/AtlasGUI/AtlasPluginManager/AtlasPluginManager.h"
	"src/AtlasGUI/AtlasCanvas/AtlasCanvas.cpp"
	"src/AtlasGUI/AtlasCanvas/AtlasCanvas.h"
)

target_include_directories(PlanetariumSoftware PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(PlanetariumSoftware PRIVATE
	wxWidgets::wxWidgets
	OpenGL::GL
)

if(MSVC)
	# Suppress the C28251 warning (inconsistent SAL annotations)
	target_compile_options(PlanetariumSoftware PRIVATE /wd28251)
endif()