#include "precompiledHeaders.h"

#include "scene.h"
#include "component.h"
#include "renderer2D.h"
#include "entity.h"
#include "sceneCamera.h"

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

    void Scene::destroyEntity(Entity entity) 
    {
        _registry.destroy(entity.getHandle());
    }

    void Scene::onUpdate(Timestep ts) 
    {
        // Updates scripts
        {
            _registry.view<NativeScriptComponent>().each([=](auto entity, auto& nativeScriptComponent)
            {
                if (!nativeScriptComponent._instance)
                {
                    nativeScriptComponent.instantiateFunction();
                    nativeScriptComponent._instance->_entity = Entity{ entity, this };
                    nativeScriptComponent.onCreateFunction(nativeScriptComponent._instance);
                }

                nativeScriptComponent.onUpdateFunction(nativeScriptComponent._instance, ts);
            });
        }

        // Renders 2D sprites
        Camera* mainCamera = nullptr;
        glm::mat4 mainCameraTransform;
        {
            auto view = _registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                const auto&[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

                if (camera._primary)
                {
                    mainCamera = &camera._camera;
                    mainCameraTransform = transform.getTransform();
                    break;
                }
            }
        }
        
        if (mainCamera)
        {
            auto group = _registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

            if (group.size())
            {
                Renderer2D::beginScene(mainCamera->getProjection(), mainCameraTransform);

                for (auto entity : group)
                {
                    const auto&[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                    Renderer2D::drawQuad(transform.getTransform(), sprite._color);
                }

                Renderer2D::endScene();
            }
        }

    }
    
    void Scene::onViewportResize(uint32_t width, uint32_t height) 
    {
        _viewportWidth = width;
        _viewportHeight = height;

        auto view = _registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent._fixedAspectRatio)
            {
                cameraComponent._camera.setViewportSize(width, height);
            }
        }
    }

    // template<typename T>
    // void Scene::onComponentAdded(Entity entity, T& component)
    // {
    //     static_assert(true);
    // }

    template<>
    void Scene::onComponentAdded<TagComponent>(Entity entity, TagComponent& component)
    {
    }

    template<>
    void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {
    }

    template<>
    void Scene::onComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
    }

    template<>
    void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        component._camera.setViewportSize(_viewportWidth, _viewportHeight);
    }

    template<>
    void Scene::onComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {
    }

}