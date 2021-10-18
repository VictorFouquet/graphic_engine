#pragma once

#include "precompiledHeaders.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "graphicsContext.h"

namespace GraphicEngine
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        void init() override;
        void swapBuffers() override;
    private:
        GLFWwindow* _window;
    };
}