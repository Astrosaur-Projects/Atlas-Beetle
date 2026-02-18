# CMakeList.txt : CMake project for Atlas-Beetle
cmake_minimum_required(VERSION 3.27)

project("Atlas-Beetle"
	VERSION 0.0.1
	DESCRIPTION "A home-brewed, planetarium software with plugin extensibility"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS gl core base)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(cfitsio NAMES cfitsio unofficial-cfitsio CONFIG REQUIRED)

add_subdirectory(src)