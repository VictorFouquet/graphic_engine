#pragma once

#include <GL/glew.h>
#include "core.h"
#include "vertexArray.h"

namespace GraphicEngine
{
    class IndexBuffer;
    class VertexBuffer;
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();

        virtual ~OpenGLVertexArray();

        virtual void bind()   const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const  Ref<IndexBuffer>&  indexBuffer) override;

        inline virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override { return _vertexBuffers; };
        inline virtual const Ref<IndexBuffer>& getIndexBuffer() const override { return _indexBuffer; };
    private:
        uint32_t _rendererID;
        std::vector<Ref<VertexBuffer>> _vertexBuffers;
        Ref<IndexBuffer> _indexBuffer;

    };

}