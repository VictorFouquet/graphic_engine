#include "glad/glad.h"
#include "openGLTexture.h"
#include "stb_image.h"

namespace GraphicEngine
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : _width(width), _height(height)
    {
        _internalFormat = GL_RGBA8;
        _dataFormat = GL_RGBA;
        glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
        glTextureStorage2D(_rendererID, 1, _internalFormat, _width, _height);

        glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }


    OpenGLTexture2D::OpenGLTexture2D(const std::string path)
        :_path(path)
    {
        int width, height, channels;

        stbi_set_flip_vertically_on_load(1);
        
        stbi_uc* data= stbi_load(_path.c_str(), &width, &height, &channels, 0);

        _width = width;
        _height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        if (internalFormat & dataFormat == 0)
            std::cout << "Format not supported" << std::endl;

        _internalFormat = internalFormat;
        _dataFormat = dataFormat;

        glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
        glTextureStorage2D(_rendererID, 1, internalFormat, _width, _height);

        glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(_rendererID, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    
    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        glDeleteTextures(1, &_rendererID);
    }
    
    void OpenGLTexture2D::setData(void *data, uint32_t size) 
    {
        glTextureSubImage2D(_rendererID, 0,0,0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
    }
    
    void OpenGLTexture2D::bind(uint32_t slot) const 
    {
        glBindTextureUnit(slot, _rendererID);
    }

}