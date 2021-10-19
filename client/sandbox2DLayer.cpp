#include "sandbox2DLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core.h"

Sandbox2DLayer::Sandbox2DLayer()
    : GraphicEngine::Layer("Sandbox2D"), _cameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2DLayer::onAttach() 
{
    _squareVA.reset(GraphicEngine::VertexArray::create());

    float squareVertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f, // Vertex coordinates 
         0.5f, -0.5f, 0.0f, // Vertex coordinates 
         0.5f,  0.5f, 0.0f, // Vertex coordinates 
        -0.5f,  0.5f, 0.0f, // Vertex coordinates 
    };

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    GraphicEngine::Ref<GraphicEngine::VertexBuffer> squareVB;
    squareVB.reset(GraphicEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

    squareVB->setLayout({
        { GraphicEngine::ShaderDataType::Float3, "aPos" }
    });

    _squareVA->addVertexBuffer(squareVB);

    GraphicEngine::Ref<GraphicEngine::IndexBuffer> squareIB;
    squareIB.reset(GraphicEngine::IndexBuffer::create(
        squareIndices, sizeof(squareIndices) / sizeof(uint32_t)
    ));

    _squareVA->setIndexBuffer(squareIB);

    _shader = GraphicEngine::Shader::create("client/assets/flatColor.glsl");
}

void Sandbox2DLayer::onDetach() 
{
    
}

void Sandbox2DLayer::onUpdate(GraphicEngine::Timestep timestep) 
{
    _cameraController.onUpdate(timestep);

    GraphicEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    GraphicEngine::RenderCommand::clear();


    GraphicEngine::Renderer::beginScene(_cameraController.getCamera());

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f));


    std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(_shader);
    std::dynamic_pointer_cast<GraphicEngine::OpenGLShader>(_shader)->uploadUniformFloat4(
        "u_Color", _lightBlueColor
    );

    GraphicEngine::Renderer::submit(_shader, _squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    GraphicEngine::Renderer::endScene();
}

void Sandbox2DLayer::onEvent(GraphicEngine::Event& event) 
{
    _cameraController.onEvent(event);
}

void Sandbox2DLayer::onImGuiRender() 
{
    ImGui::Begin("Settings");
        
    ImGui::ColorEdit3("Color", glm::value_ptr(_lightBlueColor));

    ImGui::End();
}
