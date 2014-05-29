cmake_minimum_required (VERSION 2.8)

project(boom)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    message("-- Setting build type to Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(WARNINGS "-fcheck-new -Wnarrowing -Woverloaded-virtual -Wshadow -Wunused-parameter -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNICODE -D__STDC_CONSTANT_MACROS -Wall -std=c++11 ${WARNINGS} -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g3")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

set(SHARED_NAME "boom-shared")
set(CLIENT_NAME "boom-client")
set(SERVER_NAME "boom-server")

add_subdirectory(src)
