#pragma once

#include "glm/glm.hpp"

namespace GraphicEngine
{

    struct MeshComponent
    {
        float _value;
        MeshComponent() = default;
    };

    struct TransformComponent
    {
        glm::mat4 _transform = glm::mat4(1.0f);

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4 transform)
            : _transform(transform) {}
        
        // operator glm::mat4&() { return _transform; }
        operator const glm::mat4&() { return _transform; }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 _color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const glm::vec4 color)
            : _color(color) {}
        
        operator glm::vec4&() { return _color; }
        operator const glm::vec4&() { return _color; }
    };

    struct TagComponent
    {
        std::string _tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : _tag(tag) {}
    };

}
