#pragma once

#include "entt.hpp"
#include "precompiledHeaders.h"

#include "scene.h"

namespace GraphicEngine
{
    
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        template<typename T>
        bool hasComponent()
        {
            return _scene->_registry.all_of<T>(_entityHandle);
        }
        
        template<typename T, typename... Args>
        T& addComponent(Args&&... args)
        {
            if (hasComponent<T>())
            {
                std::cout << "Entity already has component" << std::endl;
            }

            return _scene->_registry.emplace<T>(_entityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& getComponent()
        {
            if (!hasComponent<T>())
            {
                std::cout << "Entity doesn't have component" << std::endl;
            }

            return _scene->_registry.get<T>(_entityHandle);
        }

        template<typename T>
        void removeComponent()
        {
            if (!hasComponent<T>())
            {
                std::cout << "Entity doesn't have component" << std::endl;
            }

            _scene->_registry.remove<T>(_entityHandle);
        }

        operator bool() { return (uint32_t)_entityHandle != entt::null; }
    private:
        entt::entity _entityHandle{ entt::null };
        Scene* _scene = nullptr;
    };

}