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

namespace GraphicEngine
{
    class ImGuiLayer : public Layer
    {
    #define BIND_FN(fn) std::bind(&ImGuiLayer::fn, this, std::placeholders::_1)

    public:
        ImGuiLayer();
        void onAttach() override;
        void onDetach() override;

        void onImGuiRender() override;
        
        void begin();
        void end();
    };
}