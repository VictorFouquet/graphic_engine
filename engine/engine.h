#pragma once

#include "precompiledHeaders.h"

#include "glm/glm.hpp"
#include "logic.h"

#include "window.h"
#include "layer.h"
#include "layerStack.h"
#include "imGuiLayer.h"
#include "shader.h"
#include "buffer.h"
#include "vertexArray.h"
#include "event.h"
#include "applicationEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"

#include "input.h"

namespace GraphicEngine
{
    class ImGuiLayer;

    class Engine
    {
    public:
        Engine();
        ~Engine();
        void run();
        void onEvent(Event& e);
        
        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline static Engine& get() { return *_instance; }
        inline Window& getWindow() { return *window; }
    private:
        Window* window;
        ImGuiLayer* imGuiLayer;

        static Engine* _instance;

        bool _running = true;
        LayerStack _layerStack;
        
        std::shared_ptr<VertexArray>  _vertexArray;
        std::shared_ptr<VertexArray>  _squareVA;

        std::shared_ptr<Shader> _shader;
        std::shared_ptr<Shader> _blueShader;

        bool onWindowClose(WindowCloseEvent& e);
        bool handleKeyPress(KeyPressedEvent& e);
        bool handleMouseButtonPressed(MouseMovedEvent& e);
    };
}