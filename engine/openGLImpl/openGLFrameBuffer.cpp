#include "precompiledHeaders.h"
#include "openGLFrameBuffer.h"

#include "glad/glad.h"

namespace GraphicEngine
{

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
        : _specification(spec)
    {
        invalidate();
    }
    
    OpenGLFrameBuffer::~OpenGLFrameBuffer() 
    {
        glDeleteFramebuffers(1, &_rendererID);
        glDeleteTextures(1, &_colorAttachment);
        glDeleteTextures(1, &_depthAttachment);
    }
    
    void OpenGLFrameBuffer::resize(uint32_t width, uint32_t height) 
    {
        _specification.width = width;
        _specification.height = height;

        invalidate();
    }
    
    void OpenGLFrameBuffer::invalidate() 
    {
        if (_rendererID)
        {
            glDeleteFramebuffers(1, &_rendererID);
            glDeleteTextures(1, &_colorAttachment);
            glDeleteTextures(1, &_depthAttachment);
        }

        glCreateFramebuffers(1, &_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, _colorAttachment);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _specification.width, _specification.height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, _depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _specification.width, _specification.height);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "[ERROR] Framebuffer is incomplete" << std::endl;
            
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    
    void OpenGLFrameBuffer::bind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);
        glViewport(0, 0, _specification.width, _specification.height);
    }
    
    void OpenGLFrameBuffer::unbind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
