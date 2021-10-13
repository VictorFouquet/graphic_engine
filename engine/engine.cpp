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


        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        BufferLayout layout = {
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float4, "aColor" }
        };
        
        uint32_t indices[3] = { 0, 1, 2 };


        _vertexArray.reset(VertexArray::create());

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
        vertexBuffer->bind();
        vertexBuffer->setLayout(layout);

        _vertexArray->addVertexBuffer(vertexBuffer);

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
        indexBuffer->bind();

        _vertexArray->setIndexBuffer(indexBuffer);




        _squareVA.reset(VertexArray::create());

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
            { ShaderDataType::Float3, "aPos" }
        });

        _squareVA->addVertexBuffer(squareVB);

        std::shared_ptr<IndexBuffer> squareIB; 
        squareIB.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        _squareVA->setIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec4 aColor;

            out vec3 vPosition;
            out vec4 vColor;

            void main()
            {
                vPosition = aPos;
                vColor = aColor;
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            };
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location=0) out vec4 color;

            in vec3 vPosition;
            in vec4 vColor;

            void main()
            {
                color = vec4(vPosition * 0.6 + 0.5, 1.0);
                color = vColor;
            };
        )";

        _shader.reset(new Shader(vertexSrc, fragmentSrc));





        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;

            out vec3 vPosition;

            void main()
            {
                vPosition = aPos;
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            };
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            layout(location=0) out vec4 color;

            in vec3 vPosition;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            };
        )";

        _blueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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
            
            RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::clear();

            Renderer::beginScene();
            
            _blueShader->bind();
            Renderer::submit(_squareVA);

            _shader->bind();
            Renderer::submit(_vertexArray);

            Renderer::endScene();


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
