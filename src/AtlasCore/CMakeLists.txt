add_library(AtlasCore STATIC)

target_sources(AtlasCore PRIVATE
	"AtlasStartupTasks/AtlasCreateApplicationDirectory/AtlasCreateApplicationDirectory.cpp"
	"AtlasStartupTasks/AtlasCreateDatabase/AtlasCreateDatabase.cpp"
	"AtlasStartupTasks/AtlasLoadCurl/AtlasLoadCurl.cpp"
)

target_include_directories(AtlasCore PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasCreateApplicationDirectory
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasCreateDatabase
	${CMAKE_CURRENT_SOURCE_DIR}/AtlasLoadCurl
)

target_link_libraries(AtlasCore PRIVATE
	AtlasUtilities
	wxWidgets::wxWidgets
	CURL::libcurl
	SQLite::SQLite3
)