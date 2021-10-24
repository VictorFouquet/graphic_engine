add_library(openGLImpl STATIC
    openGLBuffer.cpp
    openGLContext.cpp
    openGLFrameBuffer.cpp
    openGLRendererAPI.cpp
    openGLVertexArray.cpp
    openGLShader.cpp
    openGLTexture.cpp
)

target_include_directories(openGLImpl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(openGLImpl
    precompiledHeaders
    glm
    glfw
    stb
    engine
    renderer
)