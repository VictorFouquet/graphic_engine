#pragma once

#include "precompiledHeaders.h"
#include "renderCommand.h"
#include "vertexArray.h"

namespace GraphicEngine
{
    class VertexArray;

    class Renderer
    {
    public:
        static void beginScene();
        static void endScene();

        static void submit(const std::shared_ptr<VertexArray>& vertexArray);
        
        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
    };

}