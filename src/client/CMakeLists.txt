cmake_minimum_required (VERSION 2.8)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
    message("-- Setting build type to Debug")
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(src 
    Input.cpp
    InputEvent.cpp
    #KeyEvent.cpp
    #MouseEvent.cpp
    main.cpp
    Window.cpp
    BoomClient.cpp
    )

set(headers
    Action.cpp
    Action.hpp
    Health.hpp
    Health.cpp
    Behaviour.cpp
    Behaviour.hpp
    CollisionSystem.cpp
    CollisionSystem.hpp
    Entity.cpp
    Entity.hpp
    Game.cpp
    Game.hpp
    HealthSystem.cpp
    HealthSystem.hpp
    Input.hpp
    InputEvent.hpp
    GameDelta.cpp
    GameDelta.hpp
    #KeyEvent.hpp
    Position.cpp
    Position.hpp
    PositionManager.cpp
    PositionManager.hpp
    RenderObject.cpp
    RenderObject.hpp
    RenderObjectManager.cpp
    RenderObjectManager.hpp  
    Renderer.cpp
    Renderer.hpp
    Window.hpp
    Texture.hpp
    Texture.cpp
    )

add_executable(${CLIENT_NAME} ${headers} ${src})
include_directories(../shared)

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

find_package(Boost 1.49.0 COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${CLIENT_NAME} ${Boost_LIBRARIES})
endif()

target_link_libraries(${CLIENT_NAME}
    ${SHARED_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_NET_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES})
