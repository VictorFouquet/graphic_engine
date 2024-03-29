#include "openGLBuffer.h"

namespace GraphicEngine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) 
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer() 
    {
        glDeleteBuffers(1, &_rendererID);
    }
    
    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    }
    
    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    const void OpenGLVertexBuffer::setData(const void* data, uint32_t size) 
    {
        glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }




    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        : _count(count)
    {
        glCreateBuffers(1, &_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);;
    }
    
    OpenGLIndexBuffer::~OpenGLIndexBuffer() 
    {
        glDeleteBuffers(1, &_rendererID);
    }
    
    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    }
    
    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}