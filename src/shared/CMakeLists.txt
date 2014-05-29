
set(src 
    Fake.cpp
    )

set(headers
    Fake.hpp
    common.hpp
    )
add_library(${SHARED_NAME} ${src} ${headers})
