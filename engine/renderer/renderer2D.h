#pragma once

#include "camera.h"
#include "texture.h"
#include "subTexture2D.h"

namespace GraphicEngine
{
    class Renderer2D
    {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const Camera& camera, const glm::mat4& transform);
        static void beginScene(const OrthographicCamera& camera);

        static void endScene();

        static void flush();

        // Draw quads
        static void drawQuad(const glm::mat4& transform, const glm::vec4& color);
        static void drawQuad(const glm::mat4& transform, const Ref<Texture>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));

        // Flat color quads
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        // Textured quads
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, 
            const Ref<Texture>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, 
            const Ref<Texture>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));
        // Subtextured quads
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, 
            const Ref<SubTexture2D>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, 
            const Ref<SubTexture2D>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));

        // Rotated quads
        static void drawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
        static void drawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);

        static void drawRotatedQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));
        static void drawRotatedQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, float tiling = 1.0f, glm::vec4 tint = glm::vec4(1.0f));

    };
}