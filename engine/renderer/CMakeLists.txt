add_library(renderer STATIC
    buffer.cpp
    rendererAPI.cpp
    renderCommand.cpp
    renderer.cpp
    shader.cpp
    vertexArray.cpp
    camera.cpp
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(renderer
    precompiledHeaders
    openGLImpl
)