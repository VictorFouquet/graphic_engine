add_library(engine STATIC
    engine.cpp
    input.cpp
    layer.cpp
    layerStack.cpp
    orthographicCameraController.cpp
    window.cpp
)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(openGLImpl)
add_subdirectory(imGuiImpl)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    engine_core
    events
    precompiledHeaders
    glfw
    glm
    logic
    openGLImpl
    imGuiImpl
    renderer
)