#include "imGuiLayer.h"

ImGuiLayer::ImGuiLayer()
    : GraphicEngine::Layer("ImGui")
{
}

void ImGuiLayer::onAttach(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // Taken from imgui_impl_glfw.cpp
    // Keyboard mapping. Dear ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::onUpdate()
{
    ImGuiIO& io = ImGui::GetIO();
    GraphicEngine::Engine& engine = GraphicEngine::Engine::get();
    std::cout << engine.getWindow().getWidth() << std::endl;
    io.DisplaySize = ImVec2(engine.getWindow().getWidth(), engine.getWindow().getHeight());
 
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // //ImGui_ImplGlfw_NewFrame();
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::onEvent(GraphicEngine::Event& event)
{
    GraphicEngine::EventDispatcher dispatcher(event);
    dispatcher.dispatch<GraphicEngine::MouseButtonPressedEvent>  (BIND_FN(onMouseButtonPressed));
    dispatcher.dispatch<GraphicEngine::MouseButtonReleasedEvent> (BIND_FN(onMouseButtonReleased));
    dispatcher.dispatch<GraphicEngine::MouseScrolledEvent>       (BIND_FN(onMouseScrolled));
    dispatcher.dispatch<GraphicEngine::MouseMovedEvent>          (BIND_FN(onMouseMoved));
    dispatcher.dispatch<GraphicEngine::KeyPressedEvent>          (BIND_FN(onKeyPressed));
    dispatcher.dispatch<GraphicEngine::KeyReleasedEvent>         (BIND_FN(onKeyReleased));
    dispatcher.dispatch<GraphicEngine::WindowResizeEvent>        (BIND_FN(onWindowResize));
}

bool ImGuiLayer::onMouseButtonPressed(GraphicEngine::MouseButtonPressedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.getMouseButton()] = true;

    return false;
}

bool ImGuiLayer::onMouseButtonReleased(GraphicEngine::MouseButtonReleasedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[event.getMouseButton()] = false;

    return false;
}

bool ImGuiLayer::onMouseScrolled(GraphicEngine::MouseScrolledEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += event.getXOffset();
    io.MouseWheel += event.getYOffset();

    return false;
}

bool ImGuiLayer::onMouseMoved(GraphicEngine::MouseMovedEvent& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(event.getX(), event.getY());

    return false;
}

// void ImGuiLayer::onKeyTypedEvent(GraphicEngine::KeyTypedEvent& event)
// {

// }

bool ImGuiLayer::onKeyPressed(GraphicEngine::KeyPressedEvent& event)
{
    return false;
}

bool ImGuiLayer::onKeyReleased(GraphicEngine::KeyReleasedEvent& event)
{
    return false;
}

bool ImGuiLayer::onWindowResize(GraphicEngine::WindowResizeEvent& event)
{
    return false;
}