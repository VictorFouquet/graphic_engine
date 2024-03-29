#include "window.h"
#include "applicationEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"

static bool _GLFWInitialized = false;

namespace GraphicEngine
{
    Ref<Window> Window::create(const WindowProps& props)
    {
        return CreateRef<Window>(props);
    }

    Window::Window(const WindowProps& props)
    {
        init(props);
    }

    Window::~Window()
    {
        shutdown();
    }

    void Window::init(const WindowProps& props)
    {
        data.title = props.title;
        data.width = props.width;
        data.height = props.height;

        if (!_GLFWInitialized)
        {
            int success = glfwInit();

            if (!success) {
                std::cout << "Could not initialize GLFW" << std::endl;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            _GLFWInitialized = true;
        }

        window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);

        if( window == NULL ){
            std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n";
            
            glfwTerminate();
        }

        _context = CreateScope<OpenGLContext>(window);
        _context->init();
        

        glfwSetWindowUserPointer(window, &data);
        setVSync(true);

        // Sets GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            data.width = width;
            data.height = height;

            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int modes)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {    
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {    
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {    
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int modes)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:
                {    
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {    
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.eventCallback(event);
        });
    }


    void Window::shutdown()
    {
        glfwDestroyWindow(window);
    }

    void Window::onUpdate()
    {
        glfwPollEvents();
        _context->swapBuffers();
    }

    void Window::setVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        
        data.vSync = enabled;
    }

    bool Window::isVSync() const
    {
        return data.vSync;
    }
}
