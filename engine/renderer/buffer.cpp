#include "buffer.h"
#include "openGLBuffer.h"
#include "renderer.h"

namespace GraphicEngine
{

    VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }

    IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }

}