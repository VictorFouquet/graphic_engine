#pragma once

#include <GL/glew.h>

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
        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
    };

}