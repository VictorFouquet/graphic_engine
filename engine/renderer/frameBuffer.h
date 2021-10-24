#pragma once

#include "core.h"

namespace GraphicEngine
{

    struct FrameBufferSpecification
    {
        uint32_t width, height;
        uint32_t samples = 1;

        bool swapChainTarget = false;
    };

    class FrameBuffer
    {
    public:
        virtual const FrameBufferSpecification& getSpecification() const = 0;

        static Ref<FrameBuffer> create(const FrameBufferSpecification& spec);

        virtual uint32_t getColorAttachmentRendererID() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

}