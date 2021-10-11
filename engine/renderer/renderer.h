#pragma once

#include "precompiledHeaders.h"

namespace GraphicEngine
{
    enum class RendererAPI
    {
        None = 0, OpenGL = 1
        
    };
    
    class Renderer
    {
    public:
        inline static RendererAPI getAPI() { return _rendererAPI; }
    private:
        static RendererAPI _rendererAPI;
    };
}