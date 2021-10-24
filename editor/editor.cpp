#include "editor.h"
#include "editorLayer.h"

namespace GraphicEngine
{
    Editor::Editor() 
    {
        pushLayer(new EditorLayer());
    }
    
    Editor::~Editor() 
    {
        
    }
    
}