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

        void bind()   const;
        void unbind() const;
    private:
        uint32_t _rendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
        ~OpenGLIndexBuffer();

        void bind()   const;
        void unbind() const;

        inline uint32_t getCount() const { return _count; }
    private:
        uint32_t _count;
        uint32_t _rendererID;
    };

}