#include "client.h"
#include "exampleLayers.h"
#include "sandbox2DLayer.h"
#include "tileSheetLayer.h"
#include "editorLayer.h"

ClientApp::ClientApp() : GraphicEngine::Engine()
{
    GraphicEngine::Engine& engine = GraphicEngine::Engine::get();

#if TILE_DEMO
    engine.pushLayer(new TileSheetLayer());
#endif

#if RUNTIME_DEMO
    engine.pushLayer(new Sandbox2DLayer());
#endif

#if EDITOR_MODE
    engine.pushLayer(new GraphicEngine::EditorLayer());
#endif
    
    engine.run();
}

ClientApp::~ClientApp()
{

}
