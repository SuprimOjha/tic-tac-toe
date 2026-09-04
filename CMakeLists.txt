cmake_minimum_required(VERSION 3.20)
project(titan_tactics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib CONFIG QUIET)
if (NOT raylib_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib)
endif()

add_executable(titan_tactics
    src/main.cpp
    src/Game.cpp
    src/Board.cpp
)

target_include_directories(titan_tactics PRIVATE src)

if (raylib_FOUND)
    target_link_libraries(titan_tactics PRIVATE raylib)
else()
    target_link_libraries(titan_tactics PRIVATE PkgConfig::RAYLIB)
endif()

if (MSVC)
    target_compile_options(titan_tactics PRIVATE /W4)
else()
    target_compile_options(titan_tactics PRIVATE -Wall -Wextra -Wpedantic)
endif()