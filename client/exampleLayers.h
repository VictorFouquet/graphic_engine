#include "engine.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core.h"


class ExampleLayer : public GraphicEngine::Layer
{
public:
    ExampleLayer()
        : GraphicEngine::Layer("Example"), _cameraController(1280.0f / 720.0f, true), _trianglePosition(0.0f)
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


        _vertexArray = GraphicEngine::VertexArray::create();

        GraphicEngine::Ref<GraphicEngine::VertexBuffer> vertexBuffer;
        vertexBuffer = GraphicEngine::VertexBuffer::create(vertices, sizeof(vertices));
        vertexBuffer->bind();
        vertexBuffer->setLayout(layout);

        _vertexArray->addVertexBuffer(vertexBuffer);

        GraphicEngine::Ref<GraphicEngine::IndexBuffer> indexBuffer;
        indexBuffer = GraphicEngine::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
        indexBuffer->bind();

        _vertexArray->setIndexBuffer(indexBuffer);




        _squareVA = GraphicEngine::VertexArray::create();

        float squareVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, // Vertex coordinates 
                    0.0f, 0.0f, // Texture coordinates

             0.5f, -0.5f, 0.0f, // Vertex coordinates 
                    1.0f, 0.0f, // Texture coordinates

             0.5f,  0.5f, 0.0f, // Vertex coordinates 
                    1.0f, 1.0f, // Texture coordinates

            -0.5f,  0.5f, 0.0f, // Vertex coordinates 
                    0.0f, 1.0f, // Texture coordinates
        };

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        GraphicEngine::Ref<GraphicEngine::VertexBuffer> squareVB;
        squareVB = GraphicEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices));

        squareVB->setLayout({
            { GraphicEngine::ShaderDataType::Float3, "aPos" },
            { GraphicEngine::ShaderDataType::Float2, "aTexCoord" }
        });

        _squareVA->addVertexBuffer(squareVB);

        GraphicEngine::Ref<GraphicEngine::IndexBuffer> squareIB; 
        squareIB = GraphicEngine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        _squareVA->setIndexBuffer(squareIB);

        auto gradientShader = _shaderLibrary.load("client/assets/gradient.glsl");
        auto flatColorShader = _shaderLibrary.load("client/assets/flatColor.glsl");
        auto textureShader = _shaderLibrary.load("client/assets/texture.glsl");

        _checkboxTexture = GraphicEngine::Texture2D::create("client/assets/logo.png");

        std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(textureShader)->bind();
        std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(textureShader)->uploadUniformInt("u_Texture", 0);
    }

    void onUpdate(GraphicEngine::Timestep timestep) override
    {
        _timestep = timestep;
        _cameraController.onUpdate(_timestep);

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


        GraphicEngine::Renderer::beginScene(_cameraController.getCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f));

        auto flatColorShader = _shaderLibrary.get("flatColor");
        std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(flatColorShader)->bind();

        int i = 0;

        for (float y = -9.5; y < 10.5; y++)
        {
            for (float x = -9.5; x < 10.5; x++)
            {
                if (i & 1)
                    std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(flatColorShader)->uploadUniformFloat4(
                       "u_Color", _lightBlueColor
                    );
                else
                    std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(flatColorShader)->uploadUniformFloat4(
                        "u_Color", _deepBlueColor
                    );
                i++;

                glm::vec3 pos(x * 0.09f, y * 0.09f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                GraphicEngine::Renderer::submit(flatColorShader, _squareVA, transform);
            }
            i++;
        }

        // Draw textured square
        auto textureShader = _shaderLibrary.get("texture");
        _checkboxTexture->bind(0);
        GraphicEngine::Renderer::submit(
            textureShader, _squareVA,
            glm::translate(glm::mat4(1.0f), glm::vec3(1.35f, -0.8f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f))
        );

        // Draw triangle
        auto gradientShader = _shaderLibrary.get("gradient");
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _trianglePosition);
        GraphicEngine::Renderer::submit(gradientShader, _vertexArray, transform);

        GraphicEngine::Renderer::endScene();
    }

    void onImGuiRender()
    {
        ImGui::Begin("Settings");
        
        ImGui::ColorEdit3("Color 1", glm::value_ptr(_lightBlueColor));
        ImGui::ColorEdit3("Color 2", glm::value_ptr(_deepBlueColor));
        
        ImGui::Text("Stats");

        ImGui::Text("Delta Time: %f ms", _timestep * 1000);
        ImGui::Text("Refresh: %f FPS", 1 / _timestep);

        ImGui::End();
    }

    void onEvent(GraphicEngine::Event& event) override
    {
        _cameraController.onEvent(event);
    }

private:
    GraphicEngine::ShaderLibrary _shaderLibrary;

    GraphicEngine::Ref<GraphicEngine::VertexArray>  _vertexArray;
    GraphicEngine::Ref<GraphicEngine::VertexArray>  _squareVA;

    GraphicEngine::Ref<GraphicEngine::Texture2D> _checkboxTexture;

    GraphicEngine::OrthographicCameraController _cameraController;

    float _timestep;

    glm::vec3 _trianglePosition;
    float _triangleMoveSpeed = 1.0f;
    glm::mat4 _squareTransform;

    glm::vec4 _lightBlueColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    glm::vec4 _deepBlueColor  = { 0.1f, 0.2f, 0.7f, 1.0f };
};
