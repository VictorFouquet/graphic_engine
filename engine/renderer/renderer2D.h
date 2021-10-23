#pragma once

#include "camera.h"
#include "texture.h"

namespace GraphicEngine
{
    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera& camera);
        static void endScene();

        static void flush();

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, 
                                float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, 
                                float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));

        static void drawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
        static void drawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);

        static void drawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture,
                                float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));
        static void drawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture,
                                float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));

    };
}