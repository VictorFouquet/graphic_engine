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
    };

    static Renderer2DStorage* _data;

    void Renderer2D::init() 
    {
        _data = new Renderer2DStorage();
        _data->quadVertexArray = VertexArray::create();

        float squareVertices[4 * 3] = {
            -0.5f, -0.5f, 0.0f, // Vertex coordinates 
            0.5f, -0.5f, 0.0f, // Vertex coordinates 
            0.5f,  0.5f, 0.0f, // Vertex coordinates 
            -0.5f,  0.5f, 0.0f, // Vertex coordinates 
        };

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        Ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));

        squareVB->setLayout({
            { ShaderDataType::Float3, "aPos" }
        });

        _data->quadVertexArray->addVertexBuffer(squareVB);

        Ref<IndexBuffer> squareIB;
        squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        _data->quadVertexArray->setIndexBuffer(squareIB);

        _data->flatColorShader = Shader::create("client/assets/flatColor.glsl");
    }
    
    void Renderer2D::shutdown() 
    {
        delete _data;
    }
    
    void Renderer2D::beginScene(const OrthographicCamera& camera) 
    {
        _data->flatColorShader->bind();
        _data->flatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
    }
    
    void Renderer2D::endScene() 
    {
        
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, rotation, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color) 
    {
        _data->flatColorShader->bind();
        _data->flatColorShader->setFloat4("u_Color", color);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * /* add rotation here when needed */
            glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f } );

        _data->flatColorShader->setMat4("u_Transform", transform);

        _data->quadVertexArray->bind();
        RenderCommand::drawIndexed(_data->quadVertexArray);
    }

}