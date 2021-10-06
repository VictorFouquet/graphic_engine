#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "engine.h"
#include "layer.h"

#include "event.h"
#include "keyEvent.h"
#include "mouseEvent.h"
#include "applicationEvent.h"

class ImGuiLayer : public GraphicEngine::Layer
{
#define BIND_FN(fn) std::bind(&ImGuiLayer::fn, this, std::placeholders::_1)

public:
    ImGuiLayer();
    void onAttach(GLFWwindow* window) override;
    void onUpdate() override;
    void onEvent(GraphicEngine::Event& event);
private:
    bool onMouseButtonPressed(GraphicEngine::MouseButtonPressedEvent& event);
    bool onMouseButtonReleased(GraphicEngine::MouseButtonReleasedEvent& event);
    bool onMouseScrolled(GraphicEngine::MouseScrolledEvent& event);
    bool onMouseMoved(GraphicEngine::MouseMovedEvent& event);
    // void onKeyTypedEvent(GraphicEngine::KeyTypedEvent& event);
    bool onKeyPressed(GraphicEngine::KeyPressedEvent& event);
    bool onKeyReleased(GraphicEngine::KeyReleasedEvent& event);
    bool onWindowResize(GraphicEngine::WindowResizeEvent& event);
};
