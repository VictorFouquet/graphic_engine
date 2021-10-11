add_library(client STATIC
    client.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(client
    precompiledHeaders
    events
    engine
)