#pragma once

#include "precompiledHeaders.h"
#include "renderCommand.h"
#include "vertexArray.h"
#include "camera.h"
#include "shader.h"

namespace GraphicEngine
{
    class VertexArray;

    class Renderer
    {
    public:
        static void beginScene(OrthographicCamera& camera);
        static void endScene();

        static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
        
        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
    
    private:
        struct SceneData
        {
            glm::mat4 viewProjectionMatrix;
        };

        static SceneData* _sceneData;
    };

}