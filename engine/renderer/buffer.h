#pragma once

#include "precompiledHeaders.h"
#include "core.h"

namespace GraphicEngine
{

    class OpenGLVertexBuffer;
    class OpenGLIndexBuffer;
    
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static u_int32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:  return sizeof(float);
            case ShaderDataType::Float2: return sizeof(float) * 2;
            case ShaderDataType::Float3: return sizeof(float) * 3;
            case ShaderDataType::Float4: return sizeof(float) * 4;
            case ShaderDataType::Int:    return sizeof( int );
            case ShaderDataType::Int2:   return sizeof( int ) * 2;
            case ShaderDataType::Int3:   return sizeof( int ) * 3;
            case ShaderDataType::Int4:   return sizeof( int ) * 4;
            case ShaderDataType::Mat3:   return sizeof(float) * 3 * 3;
            case ShaderDataType::Mat4:   return sizeof(float) * 4 * 4;
            case ShaderDataType::Bool:   return 1;
            default:                     return 0;
        }
    }

    struct BufferElement
    {
        std::string    name;
        ShaderDataType type;
        uint32_t       size;
        uint32_t       offset;
        bool           normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
        {
        }

        uint32_t getComponentCount() const
        {
            switch (type)
            {
                case ShaderDataType::Float:  return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Int:    return 1;
                case ShaderDataType::Int2:   return 2;
                case ShaderDataType::Int3:   return 3;
                case ShaderDataType::Int4:   return 4;
                case ShaderDataType::Mat3:   return 3 * 3;
                case ShaderDataType::Mat4:   return 4 * 4;
                case ShaderDataType::Bool:   return 1;

                default:                     return 0;
            }
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}

        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : _elements(elements)
        {
            calculateOffsetAndStride();
        }
        inline uint32_t getStride() const { return _stride; }
        inline const std::vector<BufferElement>& getElements() const { return _elements; }

        std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
        std::vector<BufferElement>::iterator end()   { return _elements.end(); }

        std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
        std::vector<BufferElement>::const_iterator end()   const { return _elements.end(); }

    private:
        void calculateOffsetAndStride()
        {
            uint32_t offset = 0;
            _stride = 0;

            for (auto& element : _elements)
            {
                element.offset = offset;
                offset += element.size;
                _stride += element.size;
            }
        }

        std::vector<BufferElement> _elements;
        uint32_t _stride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void bind()   const = 0;
        virtual void unbind() const = 0;

        virtual void setLayout(const BufferLayout layout) = 0;
        virtual const BufferLayout& getLayout() const = 0;

        static Ref<VertexBuffer> create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void bind()   const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;
        
        static Ref<IndexBuffer> create(uint32_t* vertices, uint32_t size);
    };

}