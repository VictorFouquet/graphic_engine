#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "sceneCamera.h"
#include "scriptableEntity.h"

namespace GraphicEngine
{

    struct TagComponent
    {
        std::string _tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : _tag(tag) {}
    };

    struct MeshComponent
    {
        float _value;
        MeshComponent() = default;
    };

    struct TransformComponent
    {
        // glm::mat4 _transform = glm::mat4(1.0f);
        glm::vec3 _translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 _rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 _scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;

        TransformComponent(const glm::vec3& translation)
            : _translation(translation) {}
        
        // operator glm::mat4&() { return _transform; }
        // operator const glm::mat4&() { return _transform; }
        glm::mat4 getTransform() const
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), _rotation.x, { 1, 0, 0 })
                * glm::rotate(glm::mat4(1.0f), _rotation.y, { 0, 1, 0 })
                * glm::rotate(glm::mat4(1.0f), _rotation.z, { 0, 0, 1 });

            return glm::translate(glm::mat4(1.0f), _translation) * rotation * glm::scale(glm::mat4(1.0f), _scale);
        }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 _color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        SpriteRendererComponent(const glm::vec4& color)
            : _color(color) {}
        
        operator glm::vec4&() { return _color; }
        operator const glm::vec4&() { return _color; }
    };
    
    struct CameraComponent
    {
        SceneCamera _camera;
        bool _primary = true;
        bool _fixedAspectRatio = false;
        
        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct NativeScriptComponent
    {
        ScriptableEntity* _instance = nullptr;

        std::function<void()> instantiateFunction;
        std::function<void()> destroyInstanceFunction;

        std::function<void(ScriptableEntity*)> onCreateFunction;
        std::function<void(ScriptableEntity*)> onDestroyFunction;
        std::function<void(ScriptableEntity*, Timestep)> onUpdateFunction;

        template<typename T>
        void bind()
        {
            instantiateFunction      = [&]() { _instance = new T(); };
            destroyInstanceFunction  = [&]() { delete (T*)_instance; _instance = nullptr; };

            onCreateFunction  = [](ScriptableEntity* instance) { ((T*)instance)->onCreate(); };
            onDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->onDestroy(); };
            onUpdateFunction  = [](ScriptableEntity* instance, Timestep ts) { ((T*)instance)->onUpdate(ts); };
        }
    };

}
