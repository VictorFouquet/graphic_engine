cmake_minimum_required(VERSION 3.15)

project(GraphicEngine VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# By default, we will compile the editor app with a default scene
add_compile_definitions(EDITOR_MODE=true)
add_compile_definitions(CREATE_BASIC_DEMO_SCENE=false)
add_compile_definitions(CREATE_SECOND_CAMERA=false)
# Feel free to switch these values to experiment with other application.
# Note that only one app should be set to true
add_compile_definitions(RUNTIME_DEMO=false)
add_compile_definitions(TILE_DEMO=false)

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
