add_library(AtlasStartupLayers OBJECT)

target_sources(AtlasStartupLayers PRIVATE
	AtlasDownloadCatalogs/AtlasDownloadCatalogs.cpp
	AtlasResetCatalogDirectory/AtlasResetCatalogDirectory.cpp
	AtlasSetupCurl/AtlasSetupCurl.cpp
	AtlasSetupDatabase/AtlasSetupDatabase.cpp
	AtlasSetupDefaultCatalog/AtlasSetupDefaultCatalog.cpp
	AtlasSetupDirectory/AtlasSetupDirectory.cpp
)

target_include_directories(AtlasStartupLayers PUBLIC
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AtlasStartupLayers PRIVATE
	AtlasUtilities
	wxWidgets::wxWidgets
	SQLite::SQLite3
)