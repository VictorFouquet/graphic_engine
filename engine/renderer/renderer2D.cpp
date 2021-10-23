#include "renderer2D.h"

#include "precompiledHeaders.h"
#include "core.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderCommand.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace GraphicEngine
{
    
    struct QuadVertex
    {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 textureCoord;
        float textureIndex;
        float tilingFactor;
    };

    struct Renderer2DData
    {
        const uint32_t maxQuads = 10000;
        const uint32_t maxVertices = maxQuads * 4;
        const uint32_t maxIndices = maxQuads * 6;
        static const uint32_t maxTextureSlots = 32;

        Ref<VertexArray> quadVertexArray;
        Ref<VertexBuffer> quadVertexBuffer;
        Ref<Shader> textureShader;
        Ref<Texture> whiteTexture;

        uint32_t quadIndexCount = 0;
        QuadVertex* quadVertexBufferBase = nullptr;
        QuadVertex* quadVertexBufferPtr = nullptr;

        std::array<Ref<Texture>, maxTextureSlots> textureSlots;
        uint32_t textureSlotIndex = 1; // 0 is white texture

        glm::vec4 quadVertexPositions[4];
    };

    static Renderer2DData _data;

    void Renderer2D::init() 
    {
        _data.quadVertexArray = VertexArray::create();

        _data.quadVertexBuffer = VertexBuffer::create(_data.maxVertices * sizeof(QuadVertex));

        _data.quadVertexBuffer->setLayout({
            { ShaderDataType::Float3, "a_Pos" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_textureCoord" },
            { ShaderDataType::Float,  "a_textureIndex" },
            { ShaderDataType::Float,  "a_TilingFactor" },
        });

        _data.quadVertexArray->addVertexBuffer(_data.quadVertexBuffer);

        _data.quadVertexBufferBase = new QuadVertex[_data.maxVertices];

        uint32_t* quadIndices = new uint32_t[_data.maxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < _data.maxIndices; i+= 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> quadIB = IndexBuffer::create(quadIndices, _data.maxIndices);
        _data.quadVertexArray->setIndexBuffer(quadIB);
        delete quadIndices;

        _data.whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        _data.whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));
        
        int32_t samplers[_data.maxTextureSlots];
        for (uint32_t i = 0; i < _data.maxTextureSlots; i++)
            samplers[i] = i;

        _data.textureShader = Shader::create("client/assets/tiledColoredTexture.glsl");
        _data.textureShader->bind();
        _data.textureShader->setIntArray("u_Textures", samplers, _data.maxTextureSlots);


        _data.textureSlots[0] = _data.whiteTexture;

        _data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        _data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        _data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        _data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }
    
    void Renderer2D::shutdown() 
    {

    }
    
    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        _data.quadIndexCount = 0;

        _data.textureShader->bind();
        _data.textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());

        _data.quadVertexBufferPtr = _data.quadVertexBufferBase;

        _data.textureSlotIndex = 1;
    }
    
    void Renderer2D::endScene() 
    {
        uint32_t dataSize = (uint8_t*)_data.quadVertexBufferPtr - (uint8_t*)_data.quadVertexBufferBase;
        _data.quadVertexBuffer->setData(_data.quadVertexBufferBase, dataSize);

        flush();
    }
    
    void Renderer2D::flush() 
    {
        for (uint32_t i = 0; i < _data.textureSlotIndex; i++)
        {
            _data.textureSlots[i]->bind(i);
        }

        RenderCommand::drawIndexed(_data.quadVertexArray, _data.quadIndexCount);
    }
      //-------------------------------+
     //             FLAT COLOR QUAD   /
    //-------------------------------+
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) 
    {
        const float textureIndex = 0.0f;
        const float tilingFactor = 1.0f;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[0];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[1];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[2];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[3];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadIndexCount += 6;
    }
      //-------------------------------+
     //               TEXTURED QUAD   /
    //-------------------------------+

    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size,
                            const Ref<Texture>& texture, float tiling, glm::vec4 tint) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture, tiling, tint);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size,
                            const Ref<Texture>& texture, float tiling, glm::vec4 tint) 
    {
        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < _data.textureSlotIndex; i++)
        {
            if (*_data.textureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)_data.textureSlotIndex;
            _data.textureSlots[_data.textureSlotIndex] = texture;
            _data.textureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[0];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[1];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[2];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[3];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadIndexCount += 6;
    }
      //-------------------------------+
     //           ROTATED QUAD -FLAT  /
    //-------------------------------+
    void Renderer2D::drawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color) 
    {
        drawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color);
    }
    
    void Renderer2D::drawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color) 
    {
        const float textureIndex = 0.0f;
        const float tilingFactor = 1.0f;

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[0];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[1];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[2];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[3];
        _data.quadVertexBufferPtr->color = color;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tilingFactor;

        _data.quadVertexBufferPtr++;

        _data.quadIndexCount += 6;
    }
      //-------------------------------+
     //        ROTATED QUAD -TEXTURE  /
    //-------------------------------+
    void Renderer2D::drawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
                                    const Ref<Texture>& texture, float tiling, glm::vec4 tint) 
    {
        drawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tiling, tint);
    }
    
    void Renderer2D::drawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
                                    const Ref<Texture>& texture, float tiling, glm::vec4 tint) 
    {
        constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < _data.textureSlotIndex; i++)
        {
            if (*_data.textureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = (float)_data.textureSlotIndex;
            _data.textureSlots[_data.textureSlotIndex] = texture;
            _data.textureSlotIndex++;
        }

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
                              glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[0];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[1];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 0.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[2];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 1.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadVertexBufferPtr->position = transform * _data.quadVertexPositions[3];
        _data.quadVertexBufferPtr->color = tint;
        _data.quadVertexBufferPtr->textureCoord = { 0.0f, 1.0f };
        _data.quadVertexBufferPtr->textureIndex = textureIndex;
        _data.quadVertexBufferPtr->tilingFactor = tiling;

        _data.quadVertexBufferPtr++;

        _data.quadIndexCount += 6;
    }

}