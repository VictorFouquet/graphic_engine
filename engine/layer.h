#pragma once

#include <GLFW/glfw3.h>

#include "precompiledHeaders.h"
#include "event.h"

namespace GraphicEngine
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach(GLFWwindow* window) {};
        virtual void onDetach() {};
        virtual void onUpdate() {};
        virtual void onEvent(Event& e) {};

        inline const std::string& getName() const { return _debugName; }
    protected:
        std::string _debugName;
    };
} // namespace GraphicEngine