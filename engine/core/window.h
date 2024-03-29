#pragma once

#include "core.h"
#include "precompiledHeaders.h"
#include "event.h"
#include "graphicsContext.h"
#include "openGLContext.h"

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


namespace GraphicEngine
{
    struct WindowProps
    {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string& title="Graphic Engine", unsigned int width=1280.0f, unsigned int height=720.0f)
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
        
        inline GLFWwindow* getGLFWWindow() const { return window; }
        inline unsigned int getWidth() const { return data.width; };
        inline unsigned int getHeight() const { return data.height; };

        inline void setEventCallback(const EventCallbackFn& callback) { data.eventCallback = callback; };
        void setVSync(bool enabled);
        bool isVSync() const;

        static Ref<Window> create(const WindowProps& props = WindowProps());
    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();
    private:
        GLFWwindow* window;
        Scope<GraphicsContext> _context;
        
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
