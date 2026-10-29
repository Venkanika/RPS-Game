cmake_minimum_required(VERSION 3.16)
project(rps_doodle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib QUIET)
if(TARGET raylib)
    set(RAYLIB_TARGET raylib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED IMPORTED_TARGET raylib)
    set(RAYLIB_TARGET PkgConfig::RAYLIB)
endif()

add_executable(rps_game
    main.cpp
    input_ui.cpp
    game_logic.cpp
)

target_link_libraries(rps_game PRIVATE ${RAYLIB_TARGET})
