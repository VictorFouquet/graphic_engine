add_library(stb STATIC
    stb_image.cpp
)

target_include_directories(stb PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(stb
    precompiledHeaders
)