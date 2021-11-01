add_library(scene STATIC
    scene.cpp
    entity.cpp
    sceneCamera.cpp
    sceneSerializer.cpp
)

target_include_directories(engine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(scene
    precompiledHeaders
    engine
    renderer
    glm
    entt
)