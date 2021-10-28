#pragma once

#include "entity.h"

namespace GraphicEngine
{

    class ScriptableEntity
    {
    public:
        template<typename T>
        T& getComponent()
        {
            return _entity.getComponent<T>();
        }
    private:
        Entity _entity;
        friend class Scene;
    };

}