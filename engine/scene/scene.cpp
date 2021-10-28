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
        // Renders 2D sprites
        Camera* mainCamera = nullptr;
        glm::mat4* mainCameraTransform = nullptr;
        {
            auto view = _registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                const auto&[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera._primary)
                {
                    mainCamera = &camera._camera;
                    mainCameraTransform = &transform._transform;
                    break;
                }
            }
        }

        if (mainCamera)
        {
            Renderer2D::beginScene(mainCamera->getProjection(), *mainCameraTransform);

            auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                const auto&[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                Renderer2D::drawQuad(transform, sprite._color);
            }

            Renderer2D::endScene();
        }

    }

}