#pragma once

#include <GLFW/glfw3.h>
#include "event.h"
#include "window.h"
#include "applicationEvent.h"
#include "keyEvent.h"
#include "precompiledHeaders.h"

namespace GraphicEngine
{
    class App
    {
    public:
        App();
        ~App();
        void run();
        void onEvent(Event& e);

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool handleKeyPress(KeyPressedEvent& e);
        Window* window;
        bool _running = true;
    };
}