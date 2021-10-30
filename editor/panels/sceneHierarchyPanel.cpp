#include "sceneHierarchyPanel.h"

#include "imgui.h"

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
        int i = 0;
        _context->_registry.each([&](auto entityID)
        {
            Entity entity{ entityID, _context.get() };
            drawEntityNode(entity);
        });
        
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

    }
    
}