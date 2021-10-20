#pragma once

#include "glad/glad.h"

#include "core.h"
#include "precompiledHeaders.h"

#include "texture.h"

namespace GraphicEngine
{

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height); 
        OpenGLTexture2D(const std::string path); 
        virtual ~OpenGLTexture2D();

        virtual void setData(void *data, uint32_t size) override;

        virtual uint32_t getWidth() const override { return _width; };
        virtual uint32_t getHeight() const override { return _height; };

        virtual void bind(uint32_t slot = 0) const override;
    private:
        std::string _path;
        uint32_t _width, _height;
        uint32_t _rendererID;

        GLenum _internalFormat, _dataFormat;
    };

}