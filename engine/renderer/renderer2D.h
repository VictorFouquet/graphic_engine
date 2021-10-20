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
        // Repeated textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const int repeat);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const int repeat);
        // Tinted textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 tint);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4 tint);
        // Repeated Tinted textured quad
        static void drawQuad(const glm::vec2& position, const glm::vec2& size,
            const Ref<Texture>& texture, const int repeat, const glm::vec4 tint);
        static void drawQuad(const glm::vec3& position, const glm::vec2& size,
            const Ref<Texture>& texture, const int repeat, const glm::vec4 tint);

        // Rotated quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const glm::vec4& color);
        // Rotated textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size, const Ref<Texture>& texture);
        // Rotated tinted textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const glm::vec4 tint);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const glm::vec4 tint);
        // Rotated repeated textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int repeat);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int repeat);
        // Rotated tinted textured quad
        static void drawQuad(const glm::vec2& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int repeat, const glm::vec4 tint);
        static void drawQuad(const glm::vec3& position, const float rotation, const glm::vec2& size,
            const Ref<Texture>& texture, const int repeat, const glm::vec4 tint);

    };
}