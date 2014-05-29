cmake_minimum_required (VERSION 2.8)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    message("-- Setting build type to Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(.)
FILE(GLOB_RECURSE SRCFILES *.cpp)
FILE(GLOB_RECURSE HEADERS *.hpp)

add_executable(${CLIENT_NAME} ${HEADERS} ${SRCFILES})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2_NET REQUIRED SDL2_net)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})
include_directories(${SDL2_NET_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${CLIENT_NAME} ${OPENGL_LIBRARIES})
endif()

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_PATH})
    target_link_libraries(${CLIENT_NAME} ${GLEW_LIBRARY})
endif()

find_package(GLM REQUIRED)
if (GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${CLIENT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_NET_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES})
