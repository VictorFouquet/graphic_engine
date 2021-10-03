add_library(precompiledHeaders SHARED precompiledHeaders.cpp)

target_include_directories(precompiledHeaders PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)