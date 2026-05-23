# Usage:
# cmake -B build
# cmake --build build
cmake_minimum_required(VERSION 3.20)

project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    main.cpp

    creature.hpp
    creature.cpp

    player.hpp
    player.cpp

    monster.hpp
    monster.cpp
)

target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

target_include_directories(main PRIVATE include)