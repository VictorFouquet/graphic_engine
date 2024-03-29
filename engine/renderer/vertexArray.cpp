#include "vertexArray.h"
#include "openGLVertexArray.h"
#include "renderer.h"
#include "rendererAPI.h"

namespace GraphicEngine
{
    
    Ref<VertexArray> VertexArray::create() 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLVertexArray>();
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }

    void VertexArray::bind() const
    {
        
    }
    
    void VertexArray::unbind() const
    {
        
    }
    
    void VertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        
    }
    
    void VertexArray::setIndexBuffer(const  Ref<IndexBuffer>&  indexBuffer)
    {
        
    }

}