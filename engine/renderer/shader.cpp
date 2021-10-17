#include "shader.h"

#include "vertexArray.h"
#include "openGLShader.h"
#include "renderer.h"
#include "rendererAPI.h"

namespace GraphicEngine
{
    
    Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }
    
    Ref<Shader> Shader::create(const std::string& filepath) 
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::None: 
            std::cout << "[INFO] RendererAPI::None is not yet supported." << std::endl;
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(filepath);
        }
        
        std::cout << "[ERROR] Unknown RendererAPI." << std::endl;
        return nullptr;
    }
    
    void ShaderLibrary::add(const std::string& name, Ref<Shader>& shader) 
    {
        if (exists(name))
        {
            std::cout << "[WARNING] Shader named " << name << " does already exist." << std::endl;
            return; 
        }
        _shaders[name] = shader;
    }

    void ShaderLibrary::add(Ref<Shader>& shader) 
    {
        auto& name = shader->getName();

        add(name, shader);
    }
    
    Ref<Shader> ShaderLibrary::load(const std::string& filepath) 
    {
        auto shader = Shader::create(filepath);
        add(shader);

        return shader;
    }
    
    Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath) 
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        
        return shader;
    }
    
    Ref<Shader> ShaderLibrary::get(const std::string& name) 
    {
        if (!exists(name))
        {
            std::cout << "[WARNING] Shader named " << name << " doesn't exist." << std::endl;
            return nullptr; 
        }
        return _shaders[name];
    }
    
    bool ShaderLibrary::exists(const std::string& name) 
    {
        return _shaders.find(name) != _shaders.end();
    }

}
