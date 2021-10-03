cmake_minimum_required(VERSION 3.15)

project(GraphicEngine VERSION 0.0.1)

add_subdirectory(precompiled_headers)
add_subdirectory(events)

add_executable(GraphicEngine
    main.cpp
)

target_link_libraries(GraphicEngine
    precompiledHeaders
    events
)
