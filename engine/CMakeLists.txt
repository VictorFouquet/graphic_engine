add_library(engine STATIC
    window.cpp
    layer.cpp
    layerStack.cpp
    input.cpp
    engine.cpp
)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
add_subdirectory(openGLImpl)
add_subdirectory(renderer)
add_subdirectory(imGuiImpl)

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
    logic
    openGLImpl
    imGuiImpl
    renderer
)