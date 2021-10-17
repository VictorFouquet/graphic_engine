#pragma once

#include "glm/glm.hpp"
#include "precompiledHeaders.h"
#include "shader.h"

namespace GraphicEngine
{

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        OpenGLShader(const std::string& filepath);
        virtual ~OpenGLShader();

        virtual void bind() const override;
        virtual void unbind() const override;

        void uploadUniformInt(const std::string name, int value);

        void uploadUniformFloat(const std::string name, float value);
        void uploadUniformFloat2(const std::string name, const glm::vec2 vector);
        void uploadUniformFloat3(const std::string name, const glm::vec3 vector);
        void uploadUniformFloat4(const std::string name, const glm::vec4 vector);

        void uploadUniformMat3(const std::string name, const glm::mat3 matrix);
        void uploadUniformMat4(const std::string name, const glm::mat4 matrix);
    private:
        unsigned int compileShader(const char *src, uint32_t type);
        void linkShaderProgram(unsigned int vs, unsigned int fs);

        uint32_t _rendererID;
    };

}