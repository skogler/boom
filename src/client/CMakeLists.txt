cmake_minimum_required (VERSION 2.8)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    message("-- Setting build type to Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(src 
    main.cpp
    Action.cpp
    CollisionSystem.cpp
    Entity.cpp
    Game.cpp
    HealthSystem.cpp
    Position.cpp
    PositionManager.cpp
    RenderObject.cpp
    RenderObjectManager.cpp
    )

set(headers
    Action.hpp
    CollisionSystem.hpp
    Entity.hpp
    Game.hpp
    HealthSystem.hpp
    Position.hpp
    PositionManager.hpp
    RenderObject.hpp
    RenderObjectManager.hpp  
    )

add_executable(${CLIENT_NAME} ${headers} ${src})

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)


include_directories(${SDL2_INCLUDE_DIRS})

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

target_link_libraries(${CLIENT_NAME}
    ${SDL2_LIBRARIES}
)
