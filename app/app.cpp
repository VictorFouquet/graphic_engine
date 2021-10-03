#include "app.h"

namespace GraphicEngine
{
    #define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)
    
    App::App()
    {
        window = Window::create();
        window->setEventCallback(BIND_EVENT_FN(onEvent));
    }

    App::~App()
    {

    }

    void App::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        std::cout << e.toString() << std::endl;
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(handleKeyPress));
    }

    void App::run()
    {
        while(_running)
        {
            glClearColor(0.1,0.1,0.1,1);
            glClear(GL_COLOR_BUFFER_BIT);

            window->onUpdate();
        }
    }

    bool App::handleKeyPress(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == 256)
            _running = false;
        return _running;
    }

    bool App::onWindowClose(WindowCloseEvent& e)
    {
        _running = false;

        return _running;
    }
} // namespace GraphicEngine
