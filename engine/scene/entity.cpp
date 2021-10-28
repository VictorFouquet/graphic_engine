#include "entity.h"

namespace GraphicEngine
{

    Entity::Entity(entt::entity handle, Scene* scene)
        : _entityHandle(handle), _scene(scene) 
    {
        
    }

}