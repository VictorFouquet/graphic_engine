#include "input.h"

#include "engine.h"
#include <GLFW/glfw3.h>


namespace GraphicEngine
{
    Input* Input::_instance = new Input();

    bool Input::isKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Engine::get().getWindow().getGLFWWindow());
        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Engine::get().getWindow().getGLFWWindow());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    float Input::getMouseXImpl()
    {
        std::pair<float, float> pos = getMousePosition();
        float xpos = std::get<0>(pos);

        return xpos;
    }

    float Input::getMouseYImpl()
    {
        std::pair<float, float> pos = getMousePosition();
        float ypos = std::get<1>(pos);

        return ypos;
    }

    std::pair<float, float> Input::getMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Engine::get().getWindow().getGLFWWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }
}