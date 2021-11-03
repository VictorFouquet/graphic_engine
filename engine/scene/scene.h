#pragma once
#include "entt.hpp"
#include "timestep.h"

namespace GraphicEngine
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity(const std::string& name = std::string());
        void destroyEntity(Entity entity);
        
        auto& reg() { return _registry; }

        void onUpdate(Timestep ts);
        void onViewportResize(uint32_t width, uint32_t height);

        Entity getPrimaryCameraEntity();
    private:
        template<typename T>
        void onComponentAdded(Entity entity, T& component);
    private:
        entt::registry _registry;
        uint32_t _viewportWidth = 0, _viewportHeight = 0;
        
        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchyPanel;
    };

}