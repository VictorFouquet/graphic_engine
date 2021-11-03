add_library(imGuiImpl STATIC
    imGuiLayer.cpp
)

target_include_directories(imGuiImpl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(imGuiImpl
    precompiledHeaders
    imgui
    imGuizmo
    engine
)