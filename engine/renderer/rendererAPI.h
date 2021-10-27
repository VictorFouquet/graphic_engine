#pragma once

#include "glm/glm.hpp"
#include "core.h"
#include "precompiledHeaders.h"
#include "vertexArray.h"

namespace GraphicEngine
{
    class VertexArray;

    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };
        
    public:
        virtual ~RendererAPI() = default;
        
        virtual void init() = 0;
        virtual void clear() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        
        inline static API getAPI() { return _API; } 
    private:
        static API _API;
    };
    
}