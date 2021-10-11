add_library(openGLImpl STATIC
    openGLContext.cpp
    openGLBuffer.cpp
    openGLVertexArray.cpp
)

find_package(GLEW REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIRS}
)

target_include_directories(openGLImpl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(openGLImpl
    precompiledHeaders
    ${GLEW_LIBRARIES}
    glm
    glfw
    engine
)