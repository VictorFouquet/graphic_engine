#include "editorLayer.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "core.h"
#include "component.h"
#include "sceneSerializer.h"
#include "platformUtils.h"

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

        auto square = _activeScene->createEntity("Square");
        square.addComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

        auto cameraEntity = _activeScene->createEntity("Scene Camera");
        cameraEntity.addComponent<CameraComponent>();

        // auto secondCamera = _activeScene->createEntity("Scene Camera 2");
        // auto& cc = secondCamera.addComponent<CameraComponent>();

        // cc._primary = false;

        
        class CameraController : public ScriptableEntity
        {
        public:
            void onCreate()
            {

            }

            void onUpdate(Timestep ts)
            {
                auto& translation = getComponent<TransformComponent>()._translation;
                float speed = 5.0f;

                if (Input::isKeyPressed(65))      // AZERTY Q - Move Left
                    translation.x -= speed * ts;
                else if (Input::isKeyPressed(68)) // AZERTY D - Move Right
                    translation.x += speed * ts;
                if (Input::isKeyPressed(87))      // AZERTY Z - Move Up
                    translation.y += speed * ts;
                else if (Input::isKeyPressed(83)) // AZERTY S - Move Down
                    translation.y -= speed * ts;
            }

            void onDestroy()
            {

            }
        };

        // secondCamera.addComponent<NativeScriptComponent>().bind<CameraController>();

        _sceneHierarchyPanel.setContext(_activeScene);
    }

    void EditorLayer::onDetach() 
    {
        
    }

    void EditorLayer::onUpdate(Timestep timestep)
    {
        Renderer2D::resetStats();

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
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMinSize.x = 370.0f;

        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = 32.0f;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // if (ImGui::MenuItem("Serialize"))
                // {
                //     SceneSerializer serializer(_activeScene);
                //     serializer.serialize("editor/assets/scenes/Example.algv");
                // }

                // if (ImGui::MenuItem("Deserialize"))
                // {
                //     SceneSerializer serializer(_activeScene);
                //     serializer.deserialize("editor/assets/scenes/Example.algv");
                // }

                if (ImGui::MenuItem("New", "Ctrl+N"))
                {
                    newScene();
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                {
                    openScene();
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {
                    saveSceneAs();
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Exit"))
                    Engine::get().close();

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        _sceneHierarchyPanel.onImGuiRender();
        
        ImGui::Begin("Renderer2D Stats");

        auto stats = Renderer2D::getStats();
        ImGui::Text("Draw calls: %d", stats.drawCalls);
        ImGui::Text("Quad: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
        ImGui::Text("Indices: %d", stats.getTotalIndexCount());

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

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FN(EditorLayer::onKeyPressed));

    }

    bool EditorLayer::onKeyPressed(KeyPressedEvent& e)
    {
        if (e.getRepeatCount() > 0)
            return false;

        // TODO: create key code file
        const unsigned int CTRL_LEFT   = 341;
        const unsigned int CTRL_RIGHT  = 345;
        const unsigned int SHIFT_LEFT  = 340;
        const unsigned int SHIFT_RIGHT = 344;
        const unsigned int N_KEY       =  78;
        const unsigned int O_KEY       =  79;
        const unsigned int S_KEY       =  83;

        bool controlPressed = Input::isKeyPressed(CTRL_LEFT) || Input::isKeyPressed(CTRL_RIGHT);
        bool shiftPressed = Input::isKeyPressed(SHIFT_LEFT) || Input::isKeyPressed(SHIFT_RIGHT);

        switch (e.GetKeyCode())
        {
            case S_KEY:
            {
                if (controlPressed && shiftPressed)
                    saveSceneAs();
                else if (controlPressed)
                    saveScene();
                break;
            }
            case N_KEY:
            {
                if (controlPressed)
                    newScene();
                break;
            }
            case O_KEY:
            {
                if (controlPressed)
                    openScene();
                break;
            }
            default:
                break;
        }
        return false;
    }
    
    void EditorLayer::newScene() 
    {
        _activeScene = CreateRef<Scene>();
        _activeScene->onViewportResize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
        _sceneHierarchyPanel.setContext(_activeScene);
    }
    
    void EditorLayer::openScene() 
    {
        std::string out = FileDialog::openFile("algv");
        if (out.size())
        {
            _activeScene = CreateRef<Scene>();
            _activeScene->onViewportResize((uint32_t)_viewportSize.x, (uint32_t)_viewportSize.y);
            _sceneHierarchyPanel.setContext(_activeScene);
            _lattestScenePath = out;

            SceneSerializer serializer(_activeScene);
            serializer.deserialize(out);
        }
    }
    
    void EditorLayer::saveScene() 
    {
        if (_lattestScenePath.size())
        {
            SceneSerializer serializer(_activeScene);
            serializer.serialize(_lattestScenePath);
        }
        else
            saveSceneAs();

    }
    
    void EditorLayer::saveSceneAs() 
    {
        std::string out = FileDialog::saveFile("algv");
        if (out.size())
        {
            _lattestScenePath = out;
            SceneSerializer serializer(_activeScene);
            serializer.serialize(out);
        }
    }
}
