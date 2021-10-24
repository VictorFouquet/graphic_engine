#pragma once

#include "engine.h"

class TileSheetLayer : public GraphicEngine::Layer
{
public:
    TileSheetLayer();
    ~TileSheetLayer() = default;

    void onAttach() override;
    void onDetach() override;
    
    void onUpdate(GraphicEngine::Timestep timestep) override;
    void onEvent(GraphicEngine::Event& event) override;
    void onImGuiRender();
private:
    GraphicEngine::OrthographicCameraController _cameraController;
    GraphicEngine::Ref<GraphicEngine::Shader> _shader;

    glm::vec4 _lightBlueColor = { 0.5f, 0.6f, 1.0f, 1.0f };

    GraphicEngine::Ref<GraphicEngine::Texture2D> _spriteSheet;
    GraphicEngine::Ref<GraphicEngine::SubTexture2D> _textureStairs, _textureBarrel, _textureTree;

    GraphicEngine::Ref<GraphicEngine::VertexArray>  _squareVA;

    uint32_t _mapWidth, _mapHeight;
    std::unordered_map<char, GraphicEngine::Ref<GraphicEngine::SubTexture2D>> _textureMap;
};