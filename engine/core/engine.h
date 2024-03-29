#pragma once

#include "precompiledHeaders.h"


#include "glm/glm.hpp"

#include "timestep.h"

#include "renderer.h"
#include "renderer2D.h"
#include "window.h"
#include "layer.h"
#include "layerStack.h"
#include "imGuiLayer.h"
#include "openGLShader.h"
#include "shader.h"
#include "texture.h"
#include "subTexture2D.h"
#include "buffer.h"
#include "frameBuffer.h"
#include "vertexArray.h"
#include "camera.h"
#include "orthographicCameraController.h"
#include "scene.h"

#include "event.h"
#include "applicationEvent.h"
#include "keyEvent.h"
#include "mouseEvent.h"

#include "input.h"

//#include "glad/glad.h"

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

        inline ImGuiLayer* getImGuiLayer() { return imGuiLayer; }
        inline static Engine& get() { return *_instance; }
        inline Window& getWindow() { return *window; }

        void close();
    private:
        Ref<Window> window;
        ImGuiLayer* imGuiLayer;

        static Engine* _instance;

        bool _running = true;
        bool _minimized = false;

        LayerStack _layerStack;
        
        float _lastFrameTime = 0.0f;
        
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);
    };
}