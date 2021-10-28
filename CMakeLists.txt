cmake_minimum_required(VERSION 3.15)

project(GraphicEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_compile_definitions(RUNTIME_DEMO=true)
# add_compile_definitions(TILE_DEMO=true)
add_compile_definitions(EDITOR_MODE=true)

add_subdirectory(vendor)
add_subdirectory(precompiled_headers)
add_subdirectory(events)
add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(client)

add_executable(GraphicEngine
    main.cpp
)

target_link_libraries(GraphicEngine
    precompiledHeaders
    events
    engine
    editor
    client
)
