add_library(engine SHARED window.cpp)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine
    precompiledHeaders
    ${OPENGL_INCLUDE_DIRS}
    glfw
    events
)