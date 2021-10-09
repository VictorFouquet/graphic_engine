#include "engine.h"
#include "imGuiLayer.h"

namespace GraphicEngine
{
    #define BIND_EVENT_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)
    
    Engine* Engine::_instance = nullptr;

    Engine::Engine()
    {
        _instance = this;

        window = Window::create();
        window->setEventCallback(BIND_EVENT_FN(onEvent));

        imGuiLayer = new ImGuiLayer();
        pushOverlay(imGuiLayer);

        glGenVertexArrays(1, &_vertexArray);
        glBindVertexArray(_vertexArray);

        glGenBuffers(1, &_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;

            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            };
        )";

        std::string fragmentSrc = R"(
            #version 330 core
            layout(location=0) out vec4 color;
            void main()
            {
                color = vec4(0.8, 0.2, 0.3, 1.0);
            };
        )";

        _shader = new Shader(vertexSrc, fragmentSrc);
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

            _shader->bind();

            glBindVertexArray(_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (Layer* layer: _layerStack)
                layer->onUpdate();

            imGuiLayer->begin();
            for (Layer* layer: _layerStack)
                layer->onImGuiRender();
            imGuiLayer->end();

            // std::cout << "[INPUT] MousePos: (" << Input::getMouseX() << ", " << Input::getMouseY() << ")\n";

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
