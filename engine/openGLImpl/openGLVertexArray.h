#pragma once

#include <GL/glew.h>
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

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const  std::shared_ptr<IndexBuffer>&  indexBuffer) override;

        inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override { return _vertexBuffers; };
        inline virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override { return _indexBuffer; };
    private:
        uint32_t _rendererID;
        std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
        std::shared_ptr<IndexBuffer> _indexBuffer;

    };

}