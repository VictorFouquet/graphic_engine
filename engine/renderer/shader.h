#pragma once

#include "precompiledHeaders.h"
#include "glm/glm.hpp"

namespace GraphicEngine
{
    
    class Shader
    {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;
    
        void uploadUniformMat4(const std::string name, const glm::mat4 matrix);
        void uploadUniformFloat4(const std::string name, const glm::vec4 vector);
    private:
        uint32_t _rendererID;
    };

}
