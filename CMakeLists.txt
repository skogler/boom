cmake_minimum_required (VERSION 2.8)

project(boom)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(BINARY_NAME boom)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    message("-- Setting build type to Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(WARNINGS "-fcheck-new -Wnarrowing -Woverloaded-virtual -Wshadow -Wunused-parameter -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS -Wall -std=c++11 ${WARNINGS} -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g3")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

include_directories(src)
FILE(GLOB_RECURSE SRCFILES src/*.cpp)
add_executable(${BINARY_NAME} ${SRCFILES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${BINARY_NAME} ${OPENGL_LIBRARIES})
endif()

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_PATH})
    target_link_libraries(${BINARY_NAME} ${GLEW_LIBRARY})
endif()

find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${BINARY_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES})
