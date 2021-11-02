add_library(engine STATIC
    engine.cpp
    input.cpp
    layer.cpp
    layerStack.cpp
    window.cpp
)

target_include_directories(engine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_package(OpenGL REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
)

target_link_libraries(engine
    glad
    ${OPENGL_LIBRARIES}
    events
    precompiledHeaders
    glfw
    glm
    entt
    yaml-cpp
    openGLImpl
    imGuiImpl
    renderer
    scene
    utils
)