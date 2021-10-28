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
        auto& reg() { return _registry; }

        void onUpdate(Timestep ts);
    private:
        entt::registry _registry;

        friend class Entity;
    };

}