#include "editorLayer.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "core.h"
#include "component.h"

namespace GraphicEngine
{
    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), _cameraController(1280.0f / 720.0f, true)
    {

    }

    void EditorLayer::onAttach() 
    {
        _texture = Texture2D::create("client/assets/checkerboard.png");

        FrameBufferSpecification fbSpec;
        fbSpec.width = 1280;
        fbSpec.height = 720;
        _frameBuffer = FrameBuffer::create(fbSpec);

        _activeScene = CreateRef<Scene>();

        auto square = _activeScene->createEntity("Green Square");
        square.addComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
        _squareEntity = square;

        _cameraEntity = _activeScene->createEntity("Scene Camera");
        _cameraEntity.addComponent<CameraComponent>();

        _secondCamera = _activeScene->createEntity("Scene Camera 2");
        auto& cc = _secondCamera.addComponent<CameraComponent>();

        cc._primary = false;

        
        class CameraController : public ScriptableEntity
        {
        public:
            void onCreate()
            {

            }

            void onUpdate(Timestep ts)
            {
                auto& transform = getComponent<TransformComponent>()._transform;
                float speed = 5.0f;

                if (Input::isKeyPressed(65))      // AZERTY Q - Move Left
                    transform[3][0] -= speed * ts;
                else if (Input::isKeyPressed(68)) // AZERTY D - Move Right
                    transform[3][0] += speed * ts;
                if (Input::isKeyPressed(87))      // AZERTY Z - Move Up
                    transform[3][1] += speed * ts;
                else if (Input::isKeyPressed(83)) // AZERTY S - Move Down
                    transform[3][1] -= speed * ts;
            }

            void onDestroy()
            {

            }
        };

        _secondCamera.addComponent<NativeScriptComponent>().bind<CameraController>();

        _sceneHierarchyPanel.setContext(_activeScene);
    }

    void EditorLayer::onDetach() 
    {
        
    }

    void EditorLayer::onUpdate(Timestep timestep)
    {
        
        FrameBufferSpecification spec = _frameBuffer->getSpecification();
        if (_viewportSize.x > 0.0f && _viewportSize.y > 0.0f && // zero sized framebuffer is invalid
            (spec.width != _viewportSize.x || spec.height != _viewportSize.y)
        )
		{
			_frameBuffer->resize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
			_cameraController.onResize(_viewportSize.x, _viewportSize.y);
            _activeScene->onViewportResize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
		}

        if (_viewportFocused)
            _cameraController.onUpdate(timestep);


        _frameBuffer->bind();
        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::clear();
        _activeScene->onUpdate(timestep);
        _frameBuffer->unbind();
    }

    void EditorLayer::onImGuiRender() 
    {
        static bool dockspaceOpen = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                    Engine::get().close();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        _sceneHierarchyPanel.onImGuiRender();
        
        ImGui::Begin("Settings");
        if (_squareEntity)
        {
            ImGui::Text("%s", _squareEntity.getComponent<TagComponent>()._tag.c_str());
            auto& squareColor = _squareEntity.getComponent<SpriteRendererComponent>()._color;
            ImGui::ColorEdit3("Color", glm::value_ptr(squareColor));
            ImGui::Separator();
        }
        ImGui::DragFloat3("Camera Transform", glm::value_ptr(_cameraEntity.getComponent<TransformComponent>()._transform[3]));

        if (ImGui::Checkbox("Scene Camera 1", &_primaryCamera))
        {
            _cameraEntity.getComponent<CameraComponent>()._primary = _primaryCamera;
            _secondCamera.getComponent<CameraComponent>()._primary = !_primaryCamera;
        }

        {
            auto& camera = _secondCamera.getComponent<CameraComponent>()._camera;
            float orthoSize = camera.getOrthographicSize();

            if (ImGui::DragFloat("Second Camera Ortho Size", &orthoSize, 0.1f, 0.001f, 100.0f))
                camera.setOrthographicSize(orthoSize);
        }

        ImGui::Separator();
        ImGui::End();

        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
        ImGui::Begin("Viewport");

        _viewportFocused = ImGui::IsWindowFocused();
        Engine::get().getImGuiLayer()->setBlockEvents(!_viewportFocused);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        _viewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint64_t textureID = _frameBuffer->getColorAttachmentRendererID();

        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2( 0, 1), ImVec2( 1, 0 ) );
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::onEvent(Event& event) 
    {
        _cameraController.onEvent(event);
    }
}
