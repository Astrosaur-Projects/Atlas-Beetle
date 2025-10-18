# CMakeList.txt : CMake project for Atlas-Beetle
cmake_minimum_required(VERSION 3.12)

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

add_executable(PlanetariumSoftware)

target_sources(PlanetariumSoftware PRIVATE
	"src/main.cpp"
)

set_target_properties(PlanetariumSoftware PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)
