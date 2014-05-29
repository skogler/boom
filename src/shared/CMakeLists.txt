

set(src 
    Fake.cpp
    worldmap/Worldmap.cpp
    worldmap/Block.cpp
    worldmap/simplexnoise1234.cpp
    )

set(headers
    Fake.hpp
    common.hpp
    worldmap/Worldmap.cpp
    worldmap/Block.cpp
    worldmap/simplexnoise1234.cpp
    )

add_library(${SHARED_NAME} ${src} ${headers})

