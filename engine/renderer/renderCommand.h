#pragma once

#include "glm/glm.hpp"
#include "rendererAPI.h"

namespace GraphicEngine
{
    class VertexArray;
    class RendererAPI;

    class RenderCommand
    {
    public:
        inline static void clear()
        {
            _rendererAPI->clear();
        }

        inline static void setClearColor(const glm::vec4& color)
        {
            _rendererAPI->setClearColor(color);
        }
        
        inline static void drawIndexed(const std::shared_ptr<VertexArray>& VertexArray)
        {
            _rendererAPI->drawIndexed(VertexArray);
        }

    private:
        static RendererAPI* _rendererAPI;
    };

}