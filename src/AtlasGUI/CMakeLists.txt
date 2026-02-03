add_library(AtlasGUI STATIC)

target_sources(AtlasGUI PRIVATE
	AtlasCanvas/AtlasCanvas.cpp
	AtlasFrame/AtlasFrame.cpp
	AtlasMenuBar/AtlasMenuBar.cpp
	AtlasMenus/AtlasMenuFile/AtlasMenuFile.cpp
	AtlasMenus/AtlasMenuHelp/AtlasMenuHelp.cpp
	AtlasMenus/AtlasMenuPlugins/AtlasMenuPlugins.cpp
	AtlasMenus/AtlasMenuView/AtlasMenuView.cpp
	AtlasPluginManager/AtlasPluginManager.cpp
	AtlasCatalogManager/AtlasCatalogManager.cpp
)

target_include_directories(AtlasGUI PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasGUI PRIVATE
	wxWidgets::wxWidgets
)