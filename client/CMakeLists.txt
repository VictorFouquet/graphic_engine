add_library(client STATIC
    client.cpp
)

set(FILES_TO_COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/textures/logo.png
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/texture.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/flatColor.glsl
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/shaders/gradient.glsl
)

file(COPY ${FILES_TO_COPY}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(client
    precompiledHeaders
    events
    engine
)