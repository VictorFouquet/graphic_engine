#pragma once

#include "frameBuffer.h"

namespace GraphicEngine
{

    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& spec);
        virtual ~OpenGLFrameBuffer();

        inline virtual const FrameBufferSpecification& getSpecification() const override { return _specification; };
        inline virtual uint32_t getColorAttachmentRendererID() const override { return _colorAttachment; };

        void invalidate();

        virtual void bind() override;
        virtual void unbind() override;

    private:
        uint32_t _rendererID;
        uint32_t _colorAttachment;
        uint32_t _depthAttachment;

        FrameBufferSpecification _specification;
    };

}