#include "texture.h"
#include "renderer.h"
#include "openGLTexture.h"

namespace GraphicEngine
{
    Ref<Texture2D> Texture2D::create(const std::string& path) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }
}