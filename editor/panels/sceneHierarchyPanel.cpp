#include "sceneHierarchyPanel.h"

#include "imgui.h"
#include "imgui_internal.h"
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

        // Right click on blank space
        if (ImGui::BeginPopupContextWindow(0, 1, false))
        {
            if (ImGui::MenuItem("Create empty Entity"))
                _context->createEntity("Empty Entity");
            
            ImGui::EndPopup();
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
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity.getHandle(), flags, tag.c_str());

        if (ImGui::IsItemClicked())
        {
            _selectionContext = entity;
        }

        // Right click node
        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;
            
            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGui::TreePop();
        }

        if (entityDeleted)
        {
            _context->destroyEntity(entity);
            if (_selectionContext == entity)
                _selectionContext = {};
        }
    }
    
    static void drawVec3Control(const std::string& label, glm::vec3& values,
        float resetValue = 0.0f, float minValue = -10000.0f, float columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        // Fonts are indexed in the same order they are added in imGuiLayer.cpp
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.735f, 0.213f, 0.213f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.835f, 0.313f, 0.313f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.735f, 0.213f, 0.213f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values[0] = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, minValue, 10000.0f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PopStyleColor(3);


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values[1] = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, minValue, 10000.0f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PopStyleColor(3);


        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values[2] = resetValue;
        ImGui::PopFont();
        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, minValue, 10000.0f);
        ImGui::PopItemWidth();

        ImGui::PopStyleColor(3);

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    template<typename T, typename UIFunction>
    void drawComponent(const std::string& name, Entity entity, UIFunction uiFunction)
    {
        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen;
        treeNodeFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
        treeNodeFlags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        treeNodeFlags |= ImGuiTreeNodeFlags_Framed;
        treeNodeFlags |= ImGuiTreeNodeFlags_FramePadding;

        if (entity.hasComponent<T>())
        {
            auto& component = entity.getComponent<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
            
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

            ImGui::Separator();

            bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, name.c_str());

            ImGui::PopStyleVar();
           
            ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
           
            if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
                ImGui::OpenPopup("ComponentSettings");
            
            
            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove component"))
                    removeComponent = true;
                
                ImGui::EndPopup();
            }

            if (open)
            {
                uiFunction(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                entity.removeComponent<T>();
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

            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);
        if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");
            
        if (ImGui::BeginPopup("AddComponent"))
        {
            if (ImGui::MenuItem("Camera"))
            {
                _selectionContext.addComponent<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Sprite Renderer"))
            {
                _selectionContext.addComponent<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
        ImGui::PopItemWidth();

        ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen;
        treeNodeFlags |= ImGuiTreeNodeFlags_AllowItemOverlap;
        treeNodeFlags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        treeNodeFlags |= ImGuiTreeNodeFlags_Framed;
        treeNodeFlags |= ImGuiTreeNodeFlags_FramePadding;

        if (entity.hasComponent<TransformComponent>())
        {
            bool open = ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treeNodeFlags, "Transform");

            if (open)
            {
                auto& transformComponent = entity.getComponent<TransformComponent>();
                
                drawVec3Control("Translation", transformComponent._translation);
                
                glm::vec3 rotation = glm::degrees(transformComponent._rotation);
                drawVec3Control("Rotation", rotation);
                transformComponent._rotation = glm::radians(rotation);

                drawVec3Control("Scale", transformComponent._scale, 1.0f, 0.01f);
                ImGui::TreePop();
            }
        }

        drawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component)
        {
            ImGui::ColorEdit4("Color", glm::value_ptr(component._color));
        });

        drawComponent<CameraComponent>("Camera", entity, [](auto& component)
        {
            auto& camera = component._camera;

            ImGui::Checkbox("Primary", &component._primary);

            const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
            const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.getProjectionType()];

            if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                    {
                        currentProjectionTypeString = projectionTypeStrings[i];
                        camera.setProjectionType((SceneCamera::ProjectionType)i);
                    }

                    if (isSelected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            
            if (camera.getProjectionType() == SceneCamera::ProjectionType::Perspective)
            {
                float perspectiveFOV = glm::degrees(camera.getPerspectiveVericalFOV());
                if (ImGui::DragFloat("FOV", &perspectiveFOV, 0.1f, 0.1f, 100.0f))
                    camera.setPerspectiveVericalFOV(glm::radians(perspectiveFOV));

                float nearClip = camera.getPerspectiveNearClip();
                if (ImGui::DragFloat("Near Clip", &nearClip))
                    camera.setPerspectiveNearClip(nearClip);

                float farClip = camera.getPerspectiveFarClip();
                if (ImGui::DragFloat("Far clip", &farClip))
                    camera.setPerspectiveFarClip(farClip);
            }

            if (camera.getProjectionType() == SceneCamera::ProjectionType::Orthographic)
            {
                float orthoSize = camera.getOrthographicSize();
                if (ImGui::DragFloat("Size", &orthoSize, 0.1f, 0.1f, 100.0f))
                    camera.setOrthographicSize(orthoSize);

                float nearClip = camera.getOrthographicNearClip();
                if (ImGui::DragFloat("Near Clip", &nearClip))
                    camera.setOrthographicNearClip(nearClip);

                float farClip = camera.getOrthographicFarClip();
                if (ImGui::DragFloat("Far clip", &farClip))
                    camera.setOrthographicFarClip(farClip);

                ImGui::Checkbox("Fixed Aspect Ratio", &component._fixedAspectRatio);
            }
        });

    }
    
}