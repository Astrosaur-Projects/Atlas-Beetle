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
	"src/AtlasGraphics/AtlasFrame/AtlasFrame.cpp"
	"src/AtlasGraphics/AtlasFrame/AtlasFrame.h"
	"src/AtlasGraphics/AtlasMenuBar/AtlasMenuBar.cpp"
	"src/AtlasGraphics/AtlasMenuBar/AtlasMenuBar.h"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuOptionEnums.h"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.cpp"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuFile/AtlasMenuFile.h"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.cpp"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuHelp/AtlasMenuHelp.h"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.cpp"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuPlugins/AtlasMenuPlugins.h"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.cpp"
	"src/AtlasGraphics/AtlasMenuOptions/AtlasMenuView/AtlasMenuView.h"
	"src/AtlasGraphics/AtlasPluginManager/AtlasPluginManager.cpp"
	"src/AtlasGraphics/AtlasPluginManager/AtlasPluginManager.h"
	"src/AtlasGraphics/AtlasCanvas/AtlasCanvas.cpp"
	"src/AtlasGraphics/AtlasCanvas/AtlasCanvas.h"
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