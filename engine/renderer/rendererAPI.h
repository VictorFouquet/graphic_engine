#pragma once

#include "glm/glm.hpp"
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
        virtual void clear() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API getAPI() { return _API; } 
    private:
        static API _API;
    };
    
}