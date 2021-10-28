#include "precompiledHeaders.h"

#include "scene.h"
#include "component.h"
#include "renderer2D.h"
#include "entity.h"

namespace GraphicEngine
{

    static void onTransformConstruct(entt::registry& registry, entt::entity entity)
    {

    }

    Scene::Scene() 
    {
#if ENTT_EXAMPLE_CODE
        entt::entity entity = _registry.create();

        _registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));

        _registry.on_construct<TransformComponent>().connect<&onTransformConstruct>();

        TransformComponent& transform = _registry.get<TransformComponent>(entity);

        auto view = _registry.view<TransformComponent>();
        for (auto entity : view)
        {
            TransformComponent& transform = view.get<TransformComponent>(entity);
        }

        auto group = _registry.group<TransformComponent>(entt::get<MeshComponent>);
        for (auto entity : group)
        {
            const auto&[transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
        }
#endif
    }
    
    Scene::~Scene() 
    {
        
    }
    
    Entity Scene::createEntity(const std::string& name) 
    {
        Entity entity = { _registry.create(), this };
        
        auto& tag = entity.addComponent<TagComponent>();
        entity.addComponent<TransformComponent>();

        tag._tag = name.empty() ? "Unnamed entity" : name;

        return entity;
    }
    
    void Scene::onUpdate(Timestep ts) 
    {
        auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            const auto&[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::drawQuad(transform, sprite._color);
        }
    }

}