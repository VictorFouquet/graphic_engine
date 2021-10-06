#pragma once

#include "precompiledHeaders.h"

#include "logic.h"

#include "window.h"
#include "layer.h"
#include "layerStack.h"

#include "event.h"
#include "applicationEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"

#include "input.h"

namespace GraphicEngine
{
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
        static Engine* _instance;

        bool _running = true;
        LayerStack _layerStack;
        
        bool onWindowClose(WindowCloseEvent& e);
        bool handleKeyPress(KeyPressedEvent& e);
        bool handleMouseButtonPressed(MouseMovedEvent& e);
    };
}