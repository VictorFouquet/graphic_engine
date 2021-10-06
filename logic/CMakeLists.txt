add_library(logic SHARED logic.cpp)

target_include_directories(logic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(logic
    precompiledHeaders
)