#include "shader.h"

#include "vertexArray.h"
#include "openGLShader.h"
#include "renderer.h"
#include "rendererAPI.h"

namespace GraphicEngine
{
    
    Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }

}
