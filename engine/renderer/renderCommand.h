#pragma once

#include "glm/glm.hpp"
#include "rendererAPI.h"
#include "core.h"

namespace GraphicEngine
{
    class VertexArray;
    class RendererAPI;

    class RenderCommand
    {
    public:
        inline static void init()
        {
            _rendererAPI->init();
        }

        inline static void clear()
        {
            _rendererAPI->clear();
        }

        inline static void setClearColor(const glm::vec4& color)
        {
            _rendererAPI->setClearColor(color);
        }
        
        inline static void drawIndexed(const Ref<VertexArray>& VertexArray)
        {
            _rendererAPI->drawIndexed(VertexArray);
        }

    private:
        static RendererAPI* _rendererAPI;
    };

}