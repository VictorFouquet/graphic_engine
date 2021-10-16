add_library(client STATIC
    client.cpp
)

set(FILES_TO_COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/logo.png
)

file(COPY ${FILES_TO_COPY}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(client
    precompiledHeaders
    events
    engine
)