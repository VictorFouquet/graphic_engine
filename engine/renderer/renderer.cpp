#include "renderer.h"

namespace GraphicEngine
{
    Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

    void Renderer::beginScene(OrthographicCamera& camera) 
    {
        _sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }
    
    void Renderer::endScene() 
    {
        
    }
    
    void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) 
    {
        shader->bind();
        shader->uploadUniformMat4("u_ViewProjection", _sceneData->viewProjectionMatrix);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}