#pragma once

#include "glm/glm.hpp"

#include "texture.h"

namespace GraphicEngine
{

    class SubTexture2D
    {
    public:
        SubTexture2D(const Ref<Texture>& texture, const glm::vec2& min, const glm::vec2& max);

        inline const Ref<Texture> getTexture() const { return _texture; }
        inline const glm::vec2* getTexCoords() const { return _texCoords; }

        static Ref<SubTexture2D> createFromCoords(const Ref<Texture>& texture, const glm::vec2& coords, 
            const glm::vec2 cellsize, const glm::vec2& spriteSize = { 1.0f, 1.0f });
    private:    
        Ref<Texture> _texture;

        glm::vec2 _texCoords[4];
    };

}
