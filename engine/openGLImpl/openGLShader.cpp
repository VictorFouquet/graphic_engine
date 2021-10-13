#include "openGLShader.h"
#include <GL/glew.h>
#include "glm/gtc/type_ptr.hpp"

namespace GraphicEngine
{
    OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar *source = vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        
        
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);
            
            std::cout << "Vertex shader compilation error" << std::endl;
            std::cout << infoLog.data() << std::endl;

            return;
        }
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        glCompileShader(fragmentShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(fragmentShader);
            
            std::cout << "Fragment shader compilation error" << std::endl;
            std::cout << infoLog.data() << std::endl;
            
            return;
        }

        _rendererID = glCreateProgram();
        GLuint program = _rendererID;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            
            std::cout << "Shader link failure" << std::endl;
            std::cout << infoLog.data() << std::endl;
            
            return;
        }

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(_rendererID);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(_rendererID);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }
    
    void OpenGLShader::uploadUniformInt(const std::string name, int value) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform1i(location, value);
    }
    
    void OpenGLShader::uploadUniformFloat(const std::string name, float value) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform1f(location, value);
    }
    
    void OpenGLShader::uploadUniformFloat2(const std::string name, const glm::vec2 vector) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform2f(location, vector.x, vector.y);
    }
    
    void OpenGLShader::uploadUniformFloat3(const std::string name, const glm::vec3 vector) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform3f(location, vector.x, vector.y, vector.z);
    }
    
    void OpenGLShader::uploadUniformFloat4(const std::string name, const glm::vec4 vector) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
    }
    
    void OpenGLShader::uploadUniformMat3(const std::string name, const glm::mat3 matrix) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
    
    void OpenGLShader::uploadUniformMat4(const std::string name, const glm::mat4 matrix) 
    {
        GLint location = glGetUniformLocation(_rendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}