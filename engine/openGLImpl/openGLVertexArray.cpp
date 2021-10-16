#include "core.h"
#include "openGLVertexArray.h"

namespace GraphicEngine
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Bool:   return GL_BOOL;

            default:                     return 0;
        }
    }


    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &_rendererID);
    }
    
    OpenGLVertexArray::~OpenGLVertexArray() 
    {
        glDeleteVertexArrays(1, &_rendererID);
    }

    void OpenGLVertexArray::bind() const 
    {
        glBindVertexArray(_rendererID);
    }
    
    void OpenGLVertexArray::unbind() const 
    {
        glBindVertexArray(0);
    }
    
    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) 
    {
        if (!vertexBuffer->getLayout().getElements().size())
        {
            std::cout << "[ERROR] Could not add vertex buffer because he doesn't have a layout" << std::endl;
            return;
        }

        glBindVertexArray(_rendererID);
        vertexBuffer->bind();

        uint32_t index = 0;

        const auto& layout = vertexBuffer->getLayout();

        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.getComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.type),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.getStride(),
                (const void *)(intptr_t)element.offset
            );
            index++;
        }

        _vertexBuffers.push_back(vertexBuffer);
    }
    
    void OpenGLVertexArray::setIndexBuffer(const  Ref<IndexBuffer>&  indexBuffer) 
    {        
        glBindVertexArray(_rendererID);
        indexBuffer->bind();

        _indexBuffer = indexBuffer;
    }

}