#include "frameBuffer.h"
#include "openGLFrameBuffer.h"
#include "renderer.h"

namespace GraphicEngine
{
    
    Ref<FrameBuffer> FrameBuffer::create(const FrameBufferSpecification& spec) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFrameBuffer>(spec);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }

}