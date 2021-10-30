#pragma once
#include "engine.h"
#include "entity.h"
#include "sceneHierarchyPanel.h"

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
        Ref<VertexArray>  _squareVA;
        
        Ref<Scene> _activeScene;
        Entity _squareEntity;
        Entity _cameraEntity;
        Entity _secondCamera;
        bool _primaryCamera = true;

        glm::vec4 _lightBlueColor = { 0.5f, 0.6f, 1.0f, 1.0f };

        Ref<Texture2D> _texture;

        glm::vec2 _viewportSize = { 0.0f, 0.0f };
        bool _viewportFocused;

        SceneHierarchyPanel _sceneHierarchyPanel;
    };
}
