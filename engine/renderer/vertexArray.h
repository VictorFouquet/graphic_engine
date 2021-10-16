#pragma once

#include "core.h"
#include "precompiledHeaders.h"
#include "buffer.h"

namespace GraphicEngine
{
    class OpenGLVertexArray;

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void bind()   const = 0;
        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const  Ref<IndexBuffer>&  indexBuffer)  = 0;

        virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& getIndexBuffer() const = 0;

        static VertexArray* create();
    };
}