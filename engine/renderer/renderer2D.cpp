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
        Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
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

        // float squareVertices[4 * 5] = {
        //     -0.5f, -0.5f, 0.0f, // Vertex coordinates 
        //             0.0f, 0.0f, // Texture coordinates

        //      0.5f, -0.5f, 0.0f, // Vertex coordinates 
        //             1.0f, 0.0f, // Texture coordinates

        //      0.5f,  0.5f, 0.0f, // Vertex coordinates 
        //             1.0f, 1.0f, // Texture coordinates

        //     -0.5f,  0.5f, 0.0f, // Vertex coordinates 
        //             0.0f, 1.0f, // Texture coordinates
        // };

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

        _data->flatColorShader = Shader::create("client/assets/flatColor.glsl");
        _data->textureShader = Shader::create("client/assets/texture.glsl");
        _data->textureShader->bind();
        _data->textureShader->setInt("u_Texture", 0);
    }
    
    void Renderer2D::shutdown() 
    {
        delete _data;
    }
    
    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        _data->flatColorShader->bind();
        _data->flatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());

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
        _data->flatColorShader->bind();
        _data->flatColorShader->setFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f } );

        _data->flatColorShader->setMat4("u_Transform", transform);

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
        
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 tint) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture, tint);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 tint) 
    {
        drawQuad(position, 0.0f, size, texture, tint);
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size,
                const Ref<Texture>& texture, const int repeat, const glm::vec4 tint) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, texture, repeat, tint);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size,
                const Ref<Texture>& texture, const int repeat, const glm::vec4 tint) 
    {
        drawQuad(position, 0.0f, size, texture, repeat, tint);

    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, texture);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture) 
    {
        drawQuad({ position.x, position.y, 0.0f}, rotation, size, texture, 1);
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const int repeat) 
    {
        drawQuad({ position.x, position.y, 0.0f}, 0.0f, size, texture, repeat);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const int repeat) 
    {
        drawQuad(position, 0.0f, size, texture, repeat);
    }

    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture, const int repeat) 
    {
        drawQuad({ position.x, position.y, 0.0f}, rotation, size, texture, repeat);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture, const int repeat) 
    {
        drawQuad(position, rotation, size, texture, repeat, {1.0f, 1.0f, 1.0f, 1.0f});
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const glm::vec4 tint) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tint);
    }
    
    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const glm::vec4 tint) 
    {
        drawQuad(position, rotation, size, texture, 1, tint);
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const int repeat, const glm::vec4 tint) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, texture, repeat, tint);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
        const Ref<Texture>& texture, const int repeat, const glm::vec4 tint) 
    {
        _data->textureShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f } );

        _data->textureShader->setMat4("u_Transform", transform);
        _data->textureShader->setInt("u_Repeat", repeat);
        _data->textureShader->setFloat4("u_Tint", tint);

        texture->bind();

        _data->quadVertexArray->bind();
        RenderCommand::drawIndexed(_data->quadVertexArray);
    }
    
}