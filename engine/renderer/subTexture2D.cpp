#include "subTexture2D.h"


namespace GraphicEngine
{

    SubTexture2D::SubTexture2D(const Ref<Texture>& texture, const glm::vec2& min, const glm::vec2& max) 
        : _texture(texture)
    {
        _texCoords[0] = { min.x, min.y };
        _texCoords[1] = { max.x, min.y };
        _texCoords[2] = { max.x, max.y };
        _texCoords[3] = { min.x, max.y };
    }
    
    Ref<SubTexture2D> SubTexture2D::createFromCoords(const Ref<Texture>& texture, const glm::vec2& coords,
        const glm::vec2 cellsize, const glm::vec2& spriteSize) 
    {
        glm::vec2 min = { ( coords.x * cellsize.x) / texture->getWidth(), ( coords.y * cellsize.y) / texture->getHeight() };
        glm::vec2 max = { 
            ( ( coords.x + spriteSize.x ) * cellsize.x) / texture->getWidth(),
            ( ( coords.y + spriteSize.y ) * cellsize.y) / texture->getHeight()
        };

        Ref<SubTexture2D> result = CreateRef<SubTexture2D>(texture, min, max);

        return result;
    }

}
