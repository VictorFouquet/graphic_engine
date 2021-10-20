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
    
    struct Renderer2DStorage
    {
        Ref<VertexArray> quadVertexArray;
        // Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
        Ref<Texture> whiteTexture;
    };

    static Renderer2DStorage* _data;

    void Renderer2D::init() 
    {
        _data = new Renderer2DStorage();
        _data->quadVertexArray = VertexArray::create();

        float squareVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, // Vertex coordinates
             0.0f,  0.0f,       // Texture coordinates 
             0.5f, -0.5f, 0.0f, // Vertex coordinates 
             1.0f,  0.0f,       // Texture coordinates
             0.5f,  0.5f, 0.0f, // Vertex coordinates 
             1.0f,  1.0f,       // Texture coordinates
            -0.5f,  0.5f, 0.0f, // Vertex coordinates 
             0.0f,  1.0f        // Texture coordinates
        };



        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        Ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));

        squareVB->setLayout({
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float2, "a_TexCoord" }
        });

        _data->quadVertexArray->addVertexBuffer(squareVB);

        Ref<IndexBuffer> squareIB;
        squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        _data->quadVertexArray->setIndexBuffer(squareIB);

        _data->whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        _data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));
        
        _data->textureShader = Shader::create("client/assets/tiledColoredTexture.glsl");
        _data->textureShader->bind();
        _data->textureShader->setInt("u_Texture", 0);
    }
    
    void Renderer2D::shutdown() 
    {
        delete _data;
    }
    
    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        _data->textureShader->bind();
        _data->textureShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
    }
    
    void Renderer2D::endScene() 
    {
        
    }
      //-------------------------------+
     //             FLAT COLOR QUAD   /
    //-------------------------------+


    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, 0.0f, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) 
    {
        drawQuad(position, 0.0f, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color) 
    {
        _data->textureShader->setFloat4("u_Color", color);
        _data->whiteTexture->bind();
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f } );

        _data->textureShader->setMat4("u_Transform", transform);

        _data->quadVertexArray->bind();
        RenderCommand::drawIndexed(_data->quadVertexArray);
    }


      //-------------------------------+
     //               TEXTURED QUAD   /
    //-------------------------------+


    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture) 
    {
        drawQuad(position, 0.0f, size, texture);
    }
        
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture, color);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 color) 
    {
        drawQuad(position, 0.0f, size, texture, color);
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size,
                const Ref<Texture>& texture, const int tile, const glm::vec4 color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture, tile, color);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size,
                const Ref<Texture>& texture, const int tile, const glm::vec4 color) 
    {
        drawQuad(position, 0.0f, size, texture, tile, color);

    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, texture);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture) 
    {
        drawQuad({ position.x, position.y, 0.0f}, rotation, size, texture, 1);
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const int tile) 
    {
        drawQuad({ position.x, position.y, 0.0f}, 0.0f, size, texture, tile);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const int tile) 
    {
        drawQuad(position, 0.0f, size, texture, tile);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture, const int tile) 
    {
        drawQuad({ position.x, position.y, 0.0f}, rotation, size, texture, tile);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture, const int tile) 
    {
        drawQuad(position, rotation, size, texture, tile, {1.0f, 1.0f, 1.0f, 1.0f});
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const glm::vec4 color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, texture, color);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const glm::vec4 color) 
    {
        drawQuad(position, rotation, size, texture, 1, color);
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const int tile, const glm::vec4 color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tile, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const int tile, const glm::vec4 color) 
    {
        _data->textureShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f } );

        _data->textureShader->setMat4("u_Transform", transform);
        _data->textureShader->setInt("u_Tile", tile);
        _data->textureShader->setFloat4("u_Color", color);

        texture->bind();

        _data->quadVertexArray->bind();
        RenderCommand::drawIndexed(_data->quadVertexArray);
    }
    
}