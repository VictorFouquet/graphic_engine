#include "renderer2D.h"

#include "precompiledHeaders.h"
#include "core.h"
#include "vertexArray.h"
#include "shader.h"
#include "openGLShader.h"
#include "renderCommand.h"

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
        std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->bind();
        std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->uploadUniformMat4(
            "u_ViewProjection", camera.getViewProjectionMatrix()
        );
        std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->uploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }
    
    void Renderer2D::endScene() 
    {
        
    }
    
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) 
    {
        std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->bind();
        std::dynamic_pointer_cast<OpenGLShader>(_data->flatColorShader)->uploadUniformFloat4("u_Color", color);

        _data->quadVertexArray->bind();
        RenderCommand::drawIndexed(_data->quadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) 
    {
        drawQuad({ position.x, position.y, 0.0f }, size, color);
    }

}