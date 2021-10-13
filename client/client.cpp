#include "client.h"
#include "exampleLayers.h"

ClientApp::ClientApp() : GraphicEngine::Engine()
{
    GraphicEngine::Engine& engine = GraphicEngine::Engine::get();

    engine.pushLayer(new ExampleLayer());

    engine.run();
}

ClientApp::~ClientApp()
{

}
