#pragma once
#include "engine.h"

namespace GraphicEngine
{

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        ~EditorLayer() = default;

        void onAttach() override;
        void onDetach() override;
        
        void onUpdate(Timestep timestep) override;
        void onEvent(Event& event) override;
        void onImGuiRender();
    private:
        OrthographicCameraController _cameraController;
        Ref<Shader> _shader;
        Ref<FrameBuffer> _frameBuffer;
        
        glm::vec4 _lightBlueColor = { 0.5f, 0.6f, 1.0f, 1.0f };

        Ref<Texture2D> _texture;

        Ref<VertexArray>  _squareVA;
    };
}
