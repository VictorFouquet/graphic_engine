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
    _logoTexture = GraphicEngine::Texture2D::create("client/assets/logo.png");
}

void Sandbox2DLayer::onDetach() 
{
    
}

void Sandbox2DLayer::onUpdate(GraphicEngine::Timestep timestep)
{
    _cameraController.onUpdate(timestep);

    GraphicEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    GraphicEngine::RenderCommand::clear();


    GraphicEngine::Renderer2D::beginScene(_cameraController.getCamera());

    GraphicEngine::Renderer2D::drawQuad({ -1.0f,  0.0f },  { 0.8f,  0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    GraphicEngine::Renderer2D::drawQuad({  0.5f, -0.5f }, 45.0f, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });

    GraphicEngine::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, _logoTexture, 10, _lightBlueColor);

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
