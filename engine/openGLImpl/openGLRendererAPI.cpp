#include "openGLRendererAPI.h"
#include "core.h"

namespace GraphicEngine
{
    void OpenGLRendererAPI::init() 
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    
    void OpenGLRendererAPI::clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void OpenGLRendererAPI::setClearColor(const glm::vec4& color) 
    {
        glClearColor(color.r, color.g, color.b, color.a);
        
    }
    
    void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) 
    {
        uint32_t count = indexCount ? indexCount : vertexArray->getIndexBuffer()->getCount();

        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void OpenGLRendererAPI::setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) 
    {
        glViewport(x, y, width, height);
    }

}