#include "openGLContext.h"
//#include "glad/glad.h"

namespace GraphicEngine
{

    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : _window(window)
    {
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(_window);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return;
        }

        std::cout << "OpenGL Renderer:\n";
        std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;

    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(_window);
    }

};
