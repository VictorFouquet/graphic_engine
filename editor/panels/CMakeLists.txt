add_library(panels STATIC
    sceneHierarchyPanel.cpp
)

target_include_directories(editor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(panels
    precompiledHeaders
    imgui
    scene
    engine
)