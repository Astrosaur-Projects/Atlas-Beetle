add_library(AtlasGUI STATIC)

target_sources(AtlasGUI PRIVATE
	"AtlasCanvas/AtlasCanvas.cpp"
	"AtlasFrame/AtlasFrame.cpp"
	"AtlasMenuBar/AtlasMenuBar.cpp"
	"AtlasMenus/AtlasMenuFile/AtlasMenuFile.cpp"
	"AtlasMenus/AtlasMenuHelp/AtlasMenuHelp.cpp"
	"AtlasMenus/AtlasMenuPlugins/AtlasMenuPlugins.cpp"
	"AtlasMenus/AtlasMenuView/AtlasMenuView.cpp"
	"AtlasPluginManager/AtlasPluginManager.cpp"
	"AtlasCatalogManager/AtlasCatalogManager.cpp"
)

target_include_directories(AtlasGUI PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasCanvas
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasFrame
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasMenuBar
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasMenus
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasMenus/AtlasMenuFile
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasMenus/AtlasMenuHelp
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasMenus/AtlasMenuPlugins
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasMenus/AtlasMenuView
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasPluginManager
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasCatalogManager
)

target_link_libraries(AtlasGUI PRIVATE
	wxWidgets::wxWidgets
)