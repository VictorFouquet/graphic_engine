#include "sceneHierarchyPanel.h"

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

namespace GraphicEngine
{
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) 
    {
        setContext(context);
    }
    
    void SceneHierarchyPanel::setContext(const Ref<Scene>& context) 
    {
        _context = context;
    }
    
    void SceneHierarchyPanel::onImGuiRender() 
    {
        ImGui::Begin("Scene Hierarchy");
        _context->_registry.each([&](auto entityID)
        {
            Entity entity{ entityID, _context.get() };
            drawEntityNode(entity);
        });
        
        // Handles deselect node
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            _selectionContext = {};
        }

        ImGui::End();

        ImGui::Begin("Properties");
        if (_selectionContext)
        {
            drawComponents(_selectionContext);
        }
        ImGui::End();
    }
    
    void SceneHierarchyPanel::drawEntityNode(Entity entity) 
    {
        auto& tag = entity.getComponent<TagComponent>()._tag;
        
        ImGuiTreeNodeFlags flags = ((_selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity.getHandle(), flags, tag.c_str());

        if (ImGui::IsItemClicked())
        {
            _selectionContext = entity;
        }

        if (opened)
        {
            ImGui::TreePop();
        }

    }
    
    void SceneHierarchyPanel::drawComponents(Entity entity) 
    {
        if (entity.hasComponent<TagComponent>())
        {
            auto& tag = entity.getComponent<TagComponent>()._tag;
            
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy(buffer, tag.c_str());

            if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        if (entity.hasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& transform = entity.getComponent<TransformComponent>()._transform;
                
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);

                ImGui::TreePop();
            }
        }

        if (entity.hasComponent<SpriteRendererComponent>())
        {
            if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Texture"))
            {
                auto& color = entity.getComponent<SpriteRendererComponent>()._color;
                ImGui::ColorEdit3("Color", glm::value_ptr(color));
                
                ImGui::TreePop();
            }
        }
    }
    
}