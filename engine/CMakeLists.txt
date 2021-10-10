add_library(engine SHARED
    window.cpp
    layer.cpp
    layerStack.cpp
    input.cpp
    engine.cpp
    imGuiLayer.cpp
    openGLContext.cpp
    shader.cpp
    renderer.cpp
    openGLBuffer.cpp
    buffer.cpp
    openGLVertexArray.cpp
    vertexArray.cpp
)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine
    events
    precompiledHeaders
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    glfw
    glm
    imgui
    logic
)