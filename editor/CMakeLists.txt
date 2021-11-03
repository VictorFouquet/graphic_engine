add_library(editor STATIC
    editor.cpp
    editorLayer.cpp
)

set(FILES_TO_COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/roboto/Roboto-Regular.ttf
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/roboto/Roboto-Bold.ttf
)

file(COPY ${FILES_TO_COPY}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/fonts/roboto
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/imgui_layout/imgui.ini
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/..
)

add_subdirectory(panels)

target_include_directories(editor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(editor
    precompiledHeaders
    events
    engine
    panels
    imGuizmo
)