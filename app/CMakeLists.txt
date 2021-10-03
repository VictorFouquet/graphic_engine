add_library(app SHARED app.cpp)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(app
    precompiledHeaders
    ${OPENGL_LIBRARIES}
    glfw
    events
    engine
)