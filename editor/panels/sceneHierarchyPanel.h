#pragma once

#include "scene.h"
#include "core.h"
#include "entity.h"
#include "component.h"

namespace GraphicEngine
{

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& context);

        void setContext(const Ref<Scene>& context);
        void onImGuiRender();
    private:
        void drawEntityNode(Entity entity);
        void drawComponents(Entity entity);
    private:
        Ref<Scene> _context;
        Entity _selectionContext;
    };

}
