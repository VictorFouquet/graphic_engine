add_library(editor STATIC
    editor.cpp
    editorLayer.cpp
)

target_include_directories(editor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(editor
    precompiledHeaders
    events
    engine
)