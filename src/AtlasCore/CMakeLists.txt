add_library(AtlasCore STATIC)

target_sources(AtlasCore PRIVATE
	"AtlasStartupTasks/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.cpp"
	"AtlasStartupTasks/AtlasCreateDatabase/AtlasCreateDatabase.cpp"
	"AtlasStartupTasks/AtlasLoadCurl/AtlasLoadCurl.cpp"
	"AtlasStartupTasks/AtlasOpenDatabase/AtlasOpenDatabase.cpp"
	"AtlasStartupTasks/AtlasCreateCatalogDirectoryTable/AtlasCreateCatalogDirectoryTable.cpp"
)

target_include_directories(AtlasCore PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasStartupTasks/AtlasCreateApplicationDirectory
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasStartupTasks/AtlasCreateDatabase
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasStartupTasks/AtlasLoadCurl
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasStartupTasks/AtlasOpenDatabase
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasStartupTasks/AtlasCreateCatalogDirectoryTable
)

target_link_libraries(AtlasCore PRIVATE
	AtlasUtilities
	wxWidgets::wxWidgets
	CURL::libcurl
	SQLite::SQLite3
)