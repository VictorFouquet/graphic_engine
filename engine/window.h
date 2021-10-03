#pragma once

#include <GLFW/glfw3.h>

#include "precompiledHeaders.h"
#include "event.h"

namespace GraphicEngine
{
    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title="Event Demo", unsigned int width=800, unsigned int height=600)
            : title(title), width(width), height(height)
        {
        } 
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;
        Window(const WindowProps& props);
        ~Window();

        void onUpdate();
        
        inline unsigned int getWidth() const { return data.width; };
        inline unsigned int getHeight() const { return data.height; };

        inline void setEventCallback(const EventCallbackFn& callback) { data.eventCallback = callback; };
        void setVSync(bool enabled);
        bool isVSync() const;

        static Window* create(const WindowProps& props = WindowProps());
    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();
    private:
        GLFWwindow* window;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vSync;

            EventCallbackFn eventCallback;
        };

        WindowData data;
    };
}
