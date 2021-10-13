#include "engine.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

class ExampleLayer : public GraphicEngine::Layer
{
public:
    ExampleLayer()
        : GraphicEngine::Layer("Example"), _camera(-1.6f, 1.6f, -1.2f, 1.2f), _cameraPosition(0.0f), _trianglePosition(0.0f)
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
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
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
            uniform mat4 u_Transform;

            out vec3 vPosition;
            out vec4 vColor;

            void main()
            {
                vPosition = aPos;
                vColor = aColor;
                gl_Position = u_ViewProjection * u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

        _shader.reset(GraphicEngine::Shader::create(vertexSrc, fragmentSrc));





        std::string flatColorShaderVertexSrc = R"(
            #version 330 core

            layout (location = 0) in vec3 aPos;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 vPosition;

            void main()
            {
                vPosition = aPos;
                gl_Position = u_ViewProjection * u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
            };
        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 330 core

            layout(location=0) out vec4 color;

            uniform vec4 u_Color;

            in vec3 vPosition;

            void main()
            {
                color = u_Color;
            };
        )";

        _flatColorShader.reset(GraphicEngine::Shader::create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
    }

    void onUpdate(GraphicEngine::Timestep timestep) override
    {
        std::cout << "[CLIENT] Frame timestep (ms): " << timestep.getMilliseconds() << std::endl;

        // Handles key pressed event to move camera.
        if (GraphicEngine::Input::isKeyPressed(65))      // AZERTY Q - Move Left
            _cameraPosition.x -= _cameraMoveSpeed * timestep;
        else if (GraphicEngine::Input::isKeyPressed(68)) // AZERTY D - Move Right
            _cameraPosition.x += _cameraMoveSpeed * timestep;

        if (GraphicEngine::Input::isKeyPressed(87))      // AZERTY Z - Move Up
            _cameraPosition.y += _cameraMoveSpeed * timestep;
        else if (GraphicEngine::Input::isKeyPressed(83)) // AZERTY S - Move Down
            _cameraPosition.y -= _cameraMoveSpeed * timestep;

        if (GraphicEngine::Input::isKeyPressed(69))      // AZERTY A - AntiCW Rotation
            _cameraRotation += _cameraRotationSpeed * timestep;
        else if (GraphicEngine::Input::isKeyPressed(81)) // AZERTY E - CW Rotation
            _cameraRotation -= _cameraRotationSpeed * timestep;

        // Handles key pressed event to move triangle object
        if (GraphicEngine::Input::isKeyPressed(74))      // AZERTY J - Move Left
            _trianglePosition.x -= _triangleMoveSpeed * timestep;
        else if (GraphicEngine::Input::isKeyPressed(76)) // AZERTY D - Move Right
            _trianglePosition.x += _triangleMoveSpeed * timestep;


        if (GraphicEngine::Input::isKeyPressed(73))      // AZERTY I - Move Up
            _trianglePosition.y += _triangleMoveSpeed * timestep;
        else if (GraphicEngine::Input::isKeyPressed(75)) // AZERTY K - Move Down
            _trianglePosition.y -= _triangleMoveSpeed * timestep;


        GraphicEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        GraphicEngine::RenderCommand::clear();

        _camera.setPosition(_cameraPosition);
        _camera.setRotation(_cameraRotation);


        GraphicEngine::Renderer::beginScene(_camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(_flatColorShader)->bind();

        int i = 0;

        for (float y = -9.5; y < 10.5; y++)
        {
            for (float x = -9.5; x < 10.5; x++)
            {
                if (i & 1)
                   std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(_flatColorShader)->uploadUniformFloat4(
                       "u_Color", _lightBlueColor
                    );
                else
                    std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(_flatColorShader)->uploadUniformFloat4(
                        "u_Color", _deepBlueColor
                    );
                i++;

                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                GraphicEngine::Renderer::submit(_flatColorShader, _squareVA, transform);
            }
            i++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _trianglePosition);
        GraphicEngine::Renderer::submit(_shader, _vertexArray, transform);

        GraphicEngine::Renderer::endScene();
    }

    void onImGuiRender()
    {
        ImGui::Begin("Settings");
        
        ImGui::ColorEdit3("Color 1", glm::value_ptr(_lightBlueColor));
        ImGui::ColorEdit3("Color 2", glm::value_ptr(_deepBlueColor));

        ImGui::End();
    }

    void onEvent(GraphicEngine::Event& event) override
    {
    }

private:
    std::shared_ptr<GraphicEngine::VertexArray>  _vertexArray;
    std::shared_ptr<GraphicEngine::VertexArray>  _squareVA;

    std::shared_ptr<GraphicEngine::Shader> _shader;
    std::shared_ptr<GraphicEngine::Shader> _flatColorShader;

    GraphicEngine::OrthographicCamera _camera;

    glm::vec3 _cameraPosition;
    float _cameraMoveSpeed = 2.0f;

    float _cameraRotation = 0.0f;
    float _cameraRotationSpeed = 180.0f;

    glm::vec3 _trianglePosition;
    float _triangleMoveSpeed = 1.0f;
    glm::mat4 _squareTransform;

    glm::vec4 _lightBlueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    glm::vec4 _deepBlueColor  = { 0.1f, 0.2f, 0.7f, 1.0f };
};
