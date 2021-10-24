#include "editorLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "core.h"

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
    }

    void EditorLayer::onDetach() 
    {
        
    }

    void EditorLayer::onUpdate(Timestep timestep)
    {
        _cameraController.onUpdate(timestep);

        _frameBuffer->bind();

        RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::clear();

        Renderer2D::beginScene(_cameraController.getCamera());

        static float rotation1 = 0.0f;
        rotation1 += timestep * 20.0f;

        static float rotation2 = 0.0f;
        rotation2 -= timestep * 40.0f;
        // Draws quad with flat color
        Renderer2D::drawQuad({ -1.0f,  0.0f },  { 0.8f,  0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Renderer2D::drawRotatedQuad({  0.5f, -0.5f }, rotation1, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });

        // Draws textured quads
        Renderer2D::drawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, _texture, 10, _lightBlueColor);
        Renderer2D::drawRotatedQuad({ 0.0f, 0.0f, 0.0f }, rotation2, { 1.0f, 1.0f }, _texture, 20);

        Renderer2D::endScene();

        _frameBuffer->unbind();
    }

    void EditorLayer::onEvent(Event& event) 
    {
        _cameraController.onEvent(event);
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
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
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
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
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

        ImGui::Begin("Settings");
            
        ImGui::ColorEdit3("Color", glm::value_ptr(_lightBlueColor));

        ImGui::End();

        ImGui::Begin("Viewport");
            
        uint32_t textureID = _frameBuffer->getColorAttachmentRendererID();
        ImGui::Image((void*)textureID, ImVec2( 1280.0f, 720.0f ), ImVec2( 0, 1), ImVec2( 1, 0 ) );

        ImGui::End();


        ImGui::End();
    }

}
