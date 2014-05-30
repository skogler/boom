

set(src 
    Fake.cpp
    worldmap/Worldmap.cpp
    worldmap/Block.cpp
    worldmap/simplexnoise1234.cpp
    )

set(headers
    Fake.hpp
    common.hpp
    worldmap/Worldmap.hpp
    worldmap/Block.hpp
    worldmap/simplexnoise1234.hpp
    BoomNet.hpp
    )

add_library(${SHARED_NAME} ${src} ${headers})

