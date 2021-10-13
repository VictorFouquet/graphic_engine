#pragma once

#include <GL/glew.h>
#include "buffer.h"

namespace GraphicEngine
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void bind()   const override;
        void unbind() const override;

        inline virtual void setLayout(const BufferLayout layout) override { _layout = layout; };
        inline virtual const BufferLayout& getLayout() const override { return _layout; }

    private:
        uint32_t _rendererID;
        BufferLayout _layout;
    };


    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
        ~OpenGLIndexBuffer();

        void bind()   const override;
        void unbind() const override;

        inline uint32_t getCount() const { return _count; }
    private:
        uint32_t _count;
        uint32_t _rendererID;
    };

}