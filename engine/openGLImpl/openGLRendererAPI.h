#pragma once

#include <GL/glew.h>

#include "precompiledHeaders.h"
#include "rendererAPI.h"
#include "vertexArray.h"

namespace GraphicEngine
{    
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void clear() override;
        virtual void setClearColor(const glm::vec4& color) override;
        virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };

}