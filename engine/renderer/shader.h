#pragma once

#include "precompiledHeaders.h"


namespace GraphicEngine
{
    
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;
    
    private:
        uint32_t _rendererID;
    };

}
