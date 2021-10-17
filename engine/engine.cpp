#include "engine.h"
#include "imGuiLayer.h"
#include "GLFW/glfw3.h"
#include "core.h"

namespace GraphicEngine
{   
    Engine* Engine::_instance = nullptr;

    Engine::Engine()
    {
        _instance = this;

        window = Window::create();
        window->setEventCallback(BIND_EVENT_FN(Engine::onEvent));

        Renderer::init();

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);
    }

    Engine::~Engine()
    {
        
    }
    void Engine::pushLayer(Layer* layer)
    {
        _layerStack.pushLayer(layer);
        layer->onAttach();
    }
    
    void Engine::pushOverlay(Layer* layer)
    {
        _layerStack.pushOverlay(layer);
        layer->onAttach();
    }
    
    void Engine::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Engine::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Engine::onWindowResize));

        for (auto it = _layerStack.end(); it != _layerStack.begin();)
        {
            (*--it)->onEvent(e);
            if (e.isHandled())
                break;
        }
    }

    void Engine::run()
    {
        while(_running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - _lastFrameTime;
            _lastFrameTime = time;

            if (!_minimized)
            {
                for (Layer* layer: _layerStack)
                    layer->onUpdate(timestep);
            }

            imGuiLayer->begin();
            for (Layer* layer: _layerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            window->onUpdate();
        }
    }

    bool Engine::onWindowClose(WindowCloseEvent& e)
    {
        _running = false;

        return _running;
    }

    bool Engine::onWindowResize(WindowResizeEvent& e)
    {
        if (e.getWidth() == 0 || e.getHeight() == 0)
        {
            _minimized = true;
            return false;
        }

        _minimized = false;

        Renderer::onWindowResize(e.getWidth(), e.getHeight());
        
        return false;
    }

} // namespace GraphicEngine
