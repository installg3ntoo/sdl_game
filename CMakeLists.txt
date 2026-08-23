cmake_minimum_required(VERSION 3.20)

project(sdl_game VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/UpdateSubmodule.cmake)

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(sdl_game
    src/main.cpp
)

if(MSVC)
    target_compile_options(sdl_game PRIVATE /W4)
else()
    target_compile_options(sdl_game PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

target_compile_features(sdl_game PRIVATE cxx_std_23)
target_link_libraries(sdl_game PRIVATE SDL3::SDL3)

if(WIN32 AND TARGET SDL3::SDL3-shared)
    add_custom_command(
        TARGET sdl_game
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:SDL3::SDL3-shared>"
            "$<TARGET_FILE_DIR:sdl_game>"
        VERBATIM
    )
endif()
