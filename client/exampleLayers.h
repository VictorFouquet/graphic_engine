#include "engine.h"

class ExampleLayer : public GraphicEngine::Layer
{
public:
    ExampleLayer()
        : GraphicEngine::Layer("Example")
    {
    }

    void onUpdate() override
    {
        // std::cout << "ExampleLayer::Update" << std::endl;
    }

    void onEvent(GraphicEngine::Event& event) override
    {
        std::cout << "[LAYER1] " << event.toString() << std::endl;
    }
};

class ExampleLayer2 : public GraphicEngine::Layer
{
public:
    ExampleLayer2()
        : Layer("Example2")
    {
    }

    void onUpdate() override
    {
        // std::cout << "ExampleLayer::Update" << std::endl;
    }

    void onEvent(GraphicEngine::Event& event) override
    {
        GraphicEngine::EventDispatcher dispatcher(event);
        dispatcher.dispatch<GraphicEngine::KeyPressedEvent>(std::bind(&ExampleLayer2::keyPressedHandle, this, std::placeholders::_1));
        dispatcher.dispatch<GraphicEngine::KeyReleasedEvent>(std::bind(&ExampleLayer2::keyReleasedHandle, this, std::placeholders::_1));
    }

    bool keyPressedHandle(GraphicEngine::KeyPressedEvent& e)
    {
        e.setHandled(true);
        std::cout << "[LAYER2] " << e.toString() << std::endl;

        return true;
    }

    bool keyReleasedHandle(GraphicEngine::KeyReleasedEvent& e)
    {
        e.setHandled(true);
        std::cout << "[LAYER2] " << e.toString() << std::endl;

        return true;
    }
};