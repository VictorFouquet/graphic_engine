#include "client.h"
#include "exampleLayers.h"
#include "sandbox2DLayer.h"

ClientApp::ClientApp() : GraphicEngine::Engine()
{
    GraphicEngine::Engine& engine = GraphicEngine::Engine::get();

    // Comment one of the following lines to choose the example to run.
    
    // engine.pushLayer(new ExampleLayer());
    engine.pushLayer(new Sandbox2DLayer());
    engine.run();
}

ClientApp::~ClientApp()
{

}
