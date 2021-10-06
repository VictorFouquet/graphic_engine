#include "engine.h"

namespace GraphicEngine
{
    #define BIND_EVENT_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)
    
    Engine* Engine::_instance = nullptr;

    Engine::Engine()
    {
        _instance = this;

        window = Window::create();
        window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    Engine::~Engine()
    {
        
    }
    void Engine::pushLayer(Layer* layer)
    {
        _layerStack.pushLayer(layer);
        layer->onAttach(getWindow().getGLFWWindow());
    }
    
    void Engine::pushOverlay(Layer* layer)
    {
        _layerStack.pushOverlay(layer);
        layer->onAttach(getWindow().getGLFWWindow());
    }
    
    void Engine::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

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
            glClearColor(0.1,0.1,0.1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            for (Layer* layer: _layerStack)
                layer->onUpdate();

            std::cout << "[INPUT] MousePos: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")\n";

            window->onUpdate();
        }
    }

    bool Engine::handleKeyPress(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == 256)
            _running = false;
        return _running;
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
