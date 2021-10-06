cmake_minimum_required(VERSION 3.15)

project(GraphicEngine VERSION 0.0.1)

add_subdirectory(vendor)
add_subdirectory(precompiled_headers)
add_subdirectory(events)
add_subdirectory(engine)
add_subdirectory(logic)
add_subdirectory(client)

add_executable(GraphicEngine
    main.cpp
)

target_link_libraries(GraphicEngine
    logic
    precompiledHeaders
    events
    engine
    client
)
