#pragma once

#include "glad/glad.h"

#include "core.h"
#include "precompiledHeaders.h"
#include "rendererAPI.h"
#include "vertexArray.h"

namespace GraphicEngine
{    
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void init() override;
        virtual void clear() override;
        virtual void setClearColor(const glm::vec4& color) override;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;

        virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };

}