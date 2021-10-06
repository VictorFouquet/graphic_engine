#include "client.h"
#include "exampleLayers.h"
#include "imGuiLayer.h"

ClientApp::ClientApp() : GraphicEngine::Engine()
{
    GraphicEngine::Engine& engine = GraphicEngine::Engine::get();

    engine.pushLayer(new ExampleLayer());
    engine.pushOverlay(new ExampleLayer2());
    engine.pushOverlay(new ImGuiLayer());

    engine.run();
}

ClientApp::~ClientApp()
{

}
