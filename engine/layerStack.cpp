#include "layerStack.h"

namespace GraphicEngine
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : _layers)
            delete layer;
    }

    void LayerStack::pushLayer(Layer* layer)
    {
        _layers.emplace(_layers.begin() + _layerInsertIndex, layer);
        _layerInsertIndex++;
    }

    void LayerStack::pushOverlay(Layer* overlay)
    {
        _layers.emplace_back(overlay);
    }

    void LayerStack::popLayer(Layer* layer)
    {
        auto it = std::find(_layers.begin(), _layers.end(), layer);
        if (it != _layers.end())
        {
            _layers.erase(it);
            _layerInsertIndex--;
        }
    }

    void LayerStack::popOverlay(Layer* overlay)
    {
        auto it = std::find(_layers.begin(), _layers.end(), overlay);
        if (it != _layers.end())
            _layers.erase(it);
    }
}
