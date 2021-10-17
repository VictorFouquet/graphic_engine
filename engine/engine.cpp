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

            for (Layer* layer: _layerStack)
                layer->onUpdate(timestep);

            imGuiLayer->begin();
            for (Layer* layer: _layerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            // std::cout << "[INPUT] MousePos: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")\n";

            window->onUpdate();
        }
    }

    bool Engine::onWindowClose(WindowCloseEvent& e)
    {
        _running = false;

        return _running;
    }

    bool Engine::handleMouseButtonPressed(MouseMovedEvent& e)
    {
        int x = e.getX();
        int y = e.getY();
        add(x, y);

        return true;
    }
} // namespace GraphicEngine
