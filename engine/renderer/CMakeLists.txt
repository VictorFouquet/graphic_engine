add_library(renderer STATIC
    buffer.cpp
    frameBuffer.cpp
    rendererAPI.cpp
    renderCommand.cpp
    renderer.cpp
    renderer2D.cpp
    shader.cpp
    texture.cpp
    subTexture2D.cpp
    vertexArray.cpp
    camera.cpp
    orthographicCameraController.cpp
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(renderer
    precompiledHeaders
    engine
    openGLImpl
)