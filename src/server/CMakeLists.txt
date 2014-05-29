cmake_minimum_required (VERSION 2.8)

set(src 
    main.cpp
    )

set(headers
    
    )
add_executable(${SERVER_NAME} ${headers} ${src})
include_directories(../shared)


INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_NET REQUIRED SDL2_net)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_NET_INCLUDE_DIRS})

target_link_libraries(${SERVER_NAME}
    ${SHARED_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_NET_LIBRARIES}
    )
