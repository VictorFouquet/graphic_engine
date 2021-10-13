#include "engine.h"

#define BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

class ExampleLayer : public GraphicEngine::Layer
{
public:
    ExampleLayer()
        : GraphicEngine::Layer("Example"), _camera(-2.0f, 2.0f, -1.5f, 1.5f), _cameraPosition(0.0f)
    {
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        GraphicEngine::BufferLayout layout = {
            { GraphicEngine::ShaderDataType::Float3, "aPos" },
            { GraphicEngine::ShaderDataType::Float4, "aColor" }
        };
        
        uint32_t indices[3] = { 0, 1, 2 };


        _vertexArray.reset(GraphicEngine::VertexArray::create());

        std::shared_ptr<GraphicEngine::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(GraphicEngine::VertexBuffer::create(vertices, sizeof(vertices)));
        vertexBuffer->bind();
        vertexBuffer->setLayout(layout);

        _vertexArray->addVertexBuffer(vertexBuffer);

        std::shared_ptr<GraphicEngine::IndexBuffer> indexBuffer;
        indexBuffer.reset(GraphicEngine::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
        indexBuffer->bind();

        _vertexArray->setIndexBuffer(indexBuffer);




        _squareVA.reset(GraphicEngine::VertexArray::create());

        float squareVertices[3 * 4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<GraphicEngine::VertexBuffer> squareVB;
        squareVB.reset(GraphicEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        squareVB->setLayout({
            { GraphicEngine::ShaderDataType::Float3, "aPos" }
        });

        _squareVA->addVertexBuffer(squareVB);

        std::shared_ptr<GraphicEngine::IndexBuffer> squareIB; 
        squareIB.reset(GraphicEngine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        _squareVA->setIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec4 aColor;
            
            uniform mat4 u_ViewProjection;

            out vec3 vPosition;
            out vec4 vColor;

            void main()
            {
                vPosition = aPos;
                vColor = aColor;
                gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

        _shader.reset(new GraphicEngine::Shader(vertexSrc, fragmentSrc));





        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            
            uniform mat4 u_ViewProjection;
            
            out vec3 vPosition;

            void main()
            {
                vPosition = aPos;
                gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

        _blueShader.reset(new GraphicEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void onUpdate() override
    {
        // Handles key pressed event to move camera.
        if (GraphicEngine::Input::isKeyPressed(65))      // AZERTY Q - Move Left
            _cameraPosition.x -= _cameraMoveSpeed;
        else if (GraphicEngine::Input::isKeyPressed(68)) // AZERTY D - Move Right
            _cameraPosition.x += _cameraMoveSpeed;

        if (GraphicEngine::Input::isKeyPressed(87))      // AZERTY Z - Move Up
            _cameraPosition.y += _cameraMoveSpeed;
        else if (GraphicEngine::Input::isKeyPressed(83)) // AZERTY S - Move Down
            _cameraPosition.y -= _cameraMoveSpeed;

        if (GraphicEngine::Input::isKeyPressed(69))      // AZERTY A - AntiCW Rotation
            _cameraRotation += _cameraRotationSpeed;
        else if (GraphicEngine::Input::isKeyPressed(81)) // AZERTY E - CW Rotation
            _cameraRotation -= _cameraRotationSpeed;

        GraphicEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        GraphicEngine::RenderCommand::clear();

        _camera.setPosition(_cameraPosition);
        _camera.setRotation(_cameraRotation);

        GraphicEngine::Renderer::beginScene(_camera);
        
        GraphicEngine::Renderer::submit(_blueShader, _squareVA);
        GraphicEngine::Renderer::submit(_shader, _vertexArray);

        GraphicEngine::Renderer::endScene();
    }

    void onEvent(GraphicEngine::Event& event) override
    {

    }

private:
    std::shared_ptr<GraphicEngine::VertexArray>  _vertexArray;
    std::shared_ptr<GraphicEngine::VertexArray>  _squareVA;

    std::shared_ptr<GraphicEngine::Shader> _shader;
    std::shared_ptr<GraphicEngine::Shader> _blueShader;

    GraphicEngine::OrthographicCamera _camera;

    glm::vec3 _cameraPosition;
    float _cameraMoveSpeed = 0.1f;

    float _cameraRotation = 0.0f;
    float _cameraRotationSpeed = 1.0f;
};
