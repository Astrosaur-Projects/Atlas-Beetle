add_library(AtlasGUI STATIC)

target_sources(AtlasGUI PRIVATE
	AtlasCanvas/AtlasCanvas.cpp
	AtlasWindows/AtlasCatalogManager/AtlasCatalogManager.cpp
	AtlasFrame/AtlasFrame.cpp
	AtlasToolbar/AtlasToolbar.cpp
	AtlasMenus/AtlasMenuFile/AtlasMenuFile.cpp
	AtlasMenus/AtlasMenuView/AtlasMenuView.cpp
)

target_include_directories(AtlasGUI PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasGUI PRIVATE
	wxWidgets::wxWidgets
)