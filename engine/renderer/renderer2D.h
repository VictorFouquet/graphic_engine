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

        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        // Textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture);
        // Tiled textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const int tile);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const int tile);
        // Colored textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 color);
        // Tiled Colored textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size,
            const Ref<Texture>& texture, const int tile, const glm::vec4 color);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size,
            const Ref<Texture>& texture, const int tile, const glm::vec4 color);

        // Rotated quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
        // Rotated textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture);
        // Rotated Colored textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const glm::vec4 color);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const glm::vec4 color);
        // Rotated tiled textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int tile);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int tile);
        // Rotated Colored textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int tile, const glm::vec4 color);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int tile, const glm::vec4 color);

    };
}