#pragma once

#include "core.h"
#include "scene.h"

namespace GraphicEngine
{
    
    class SceneSerializer
    {
    public:
        SceneSerializer(const Ref<Scene>& scene);

        void serialize(const std::string& filepath);
        void serializeRunTime(const std::string& filepath);

        bool deserialize(const std::string& filepath);
        bool deserializeRunTime(const std::string& filepath);
    private:
        Ref<Scene> _scene;
    };

}