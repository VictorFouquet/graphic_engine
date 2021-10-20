#pragma once

#include "engine.h"

class Sandbox2DLayer : public GraphicEngine::Layer
{
public:
    Sandbox2DLayer();
    ~Sandbox2DLayer() = default;

    void onAttach() override;
    void onDetach() override;
    
    void onUpdate(GraphicEngine::Timestep timestep) override;
    void onEvent(GraphicEngine::Event& event) override;
    void onImGuiRender();
private:
    GraphicEngine::OrthographicCameraController _cameraController;
    GraphicEngine::Ref<GraphicEngine::Shader> _shader;

    glm::vec4 _lightBlueColor = { 0.5f, 0.6f, 1.0f, 1.0f };

    GraphicEngine::Ref<GraphicEngine::Texture2D> _logoTexture;
    GraphicEngine::Ref<GraphicEngine::VertexArray>  _squareVA;
};