#include <GL/glew.h>

#include "openGLTexture.h"
#include "stb_image.h"

namespace GraphicEngine
{

    OpenGLTexture2D::OpenGLTexture2D(const std::string path)
        :_path(path)
    {
        int width, height, channels;

        stbi_set_flip_vertically_on_load(1);
        
        stbi_uc* data= stbi_load(_path.c_str(), &width, &height, &channels, 0);

        _width = width;
        _height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &_rendererID);
        glTextureStorage2D(_rendererID, 1, GL_RGB8, _width, _height);

        glTextureParameteri(_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(_rendererID, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    
    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        glDeleteTextures(1, &_rendererID);
    }
    
    void OpenGLTexture2D::bind(uint32_t slot) const 
    {
        glBindTextureUnit(slot, _rendererID);
    }

}