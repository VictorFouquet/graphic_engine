#include "openGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <iostream>

namespace GraphicEngine
{
    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : _name(name)
    {
        unsigned int vertexShader = compileShader(vertexSrc.c_str(), 0);
        unsigned int fragmentShader = compileShader(fragmentSrc.c_str(), 1);
        linkShaderProgram(vertexShader, fragmentShader);
    }
    
    OpenGLShader::OpenGLShader(const std::string& filepath) 
    {
        // Extracts file name: path/to/texture.shader.glsl -> texture.shader
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

        _name = filepath.substr(lastSlash, count);

        std::ifstream inFile;
        inFile.open(filepath); //open the input file

        std::stringstream strStream;
        strStream << inFile.rdbuf(); //read the file
        std::string str = strStream.str(); //str holds the content of the file

        std::string start = "#type vertex";
        std::string delimiter = "#type fragment";
        auto limit = str.find(delimiter);

        // Extracts vertex shader sources.
        std::string vertexSrc = str.substr(start.length(), limit - delimiter.length());
        std::string fragmentSrc = str.substr(limit + delimiter.length(), str.length());


        const char *vertexShaderSrc = vertexSrc.c_str();
        const char *fragmentShaderSrc = fragmentSrc.c_str();

        unsigned int vertexShader = compileShader(vertexShaderSrc, 0);
        unsigned int fragmentShader = compileShader(fragmentShaderSrc, 1);

        linkShaderProgram(vertexShader, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(_rendererID);
    }

    unsigned int OpenGLShader::compileShader(const char *src, uint32_t type) 
    {
        unsigned int shader;

        if (type == 0)
            shader = glCreateShader(GL_VERTEX_SHADER);
        else
            shader = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(shader, 1, &src, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        
        
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);
            
            std::cout << "Shader compilation error" << std::endl;
            std::cout << infoLog.data() << std::endl;

            return -1;
        }

        return shader;
    }
    
    void OpenGLShader::linkShaderProgram(unsigned int vs, unsigned int fs) 
    {
        _rendererID = glCreateProgram();
        GLuint program = _rendererID;

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vs);
            glDeleteShader(fs);
            
            std::cout << "Shader link failure" << std::endl;
            std::cout << infoLog.data() << std::endl;
            
            return;
        }

        glDetachShader(program, vs);
        glDetachShader(program, fs);
    }

    void OpenGLShader::bind() const
    {
        glUseProgram(_rendererID);
    }

    void OpenGLShader::unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::setInt(const std::string& name, const int value) 
    {
        uploadUniformInt(name, value);
    }
    
    void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value) 
    {
        uploadUniformFloat3(name, value);
    }
    
    void OpenGLShader::setFloat4(const std::string& name, const glm::vec4& value) 
    {
        uploadUniformFloat4(name, value);
    }
    
    void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) 
    {
        uploadUniformMat4(name, value);
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