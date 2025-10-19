# CMakeList.txt : CMake project for Atlas-Beetle
cmake_minimum_required(VERSION 3.27)

# Enable Hot Reload for MSVC compilers if supported
if(POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Atlas-Beetle"
	VERSION 0.0.1
	DESCRIPTION "A home-brewed, planetarium software with plugin extensibility"
	LANGUAGES CXX
)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(PlanetariumSoftware WIN32)

target_sources(PlanetariumSoftware PRIVATE
	"src/main.cpp"
)

set_target_properties(PlanetariumSoftware PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

target_link_libraries(PlanetariumSoftware PRIVATE wxWidgets::wxWidgets)
