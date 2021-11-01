#include "sceneSerializer.h"

#include <fstream>
#include "yaml-cpp/yaml.h"

#include "entity.h"
#include "component.h"


namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}

namespace GraphicEngine
{
    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;

        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;

        return out;
    }

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
        : _scene(scene)
    {
        
    }
    
    static void serializeEntity(YAML::Emitter& out, Entity entity)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Value << "192837465564738291"; // TODO - change to entity UID

        if (entity.hasComponent<TagComponent>())
        {
            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap;

            auto& tag = entity.getComponent<TagComponent>()._tag;
            out << YAML::Key << "Tag" << YAML::Value << tag;

            out << YAML::EndMap;
        }


        if (entity.hasComponent<TransformComponent>())
        {
            out << YAML::Key << "Transform Component";
            out << YAML::BeginMap;

            auto& tc = entity.getComponent<TransformComponent>();
            out << YAML::Key << "Translation" << YAML::Value << tc._translation;
            out << YAML::Key << "Rotation" << YAML::Value << tc._rotation;
            out << YAML::Key << "Scale" << YAML::Value << tc._scale;

            out << YAML::EndMap;
        }

        if (entity.hasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap;

			auto& cameraComponent = entity.getComponent<CameraComponent>();
			auto& camera = cameraComponent._camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap;
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.getProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.getPerspectiveVericalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.getPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.getPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.getOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.getOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.getOrthographicFarClip();
			out << YAML::EndMap;

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent._primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent._fixedAspectRatio;

			out << YAML::EndMap;
		}

		if (entity.hasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap;

			auto& spriteRendererComponent = entity.getComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent._color;

			out << YAML::EndMap;
		}

        out << YAML::EndMap;
    }

    void SceneSerializer::serialize(const std::string& filepath) 
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        _scene->_registry.each([&](auto entityID)
        {
            Entity entity = { entityID, _scene.get() };
            if (!entity)
                return;
            
            serializeEntity(out, entity);
        });
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout(filepath);
        fout << out.c_str();
    }
    
    void SceneSerializer::serializeRunTime(const std::string& filepath) 
    {
        
    }
    
    bool SceneSerializer::deserialize(const std::string& filepath) 
    {
        std::ifstream stream(filepath);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());
        if (!data["Scene"])
            return false;
        
        std::string sceneName = data["Scene"].as<std::string>();

        auto entities = data["Entities"];

        if (entities)
        {
            for (auto entity : entities)
            {
                uint64_t uuid = entity["Entity"].as<uint64_t>();

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();
                
                Entity deserializedEntity = _scene->createEntity(name);


                auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					auto& tc = deserializedEntity.getComponent<TransformComponent>();
					tc._translation = transformComponent["Translation"].as<glm::vec3>();
					tc._rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc._scale = transformComponent["Scale"].as<glm::vec3>();
				}

                auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.addComponent<CameraComponent>();

					const auto& cameraProps = cameraComponent["Camera"];
					cc._camera.setProjectionType((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

					cc._camera.setPerspectiveVericalFOV(cameraProps["PerspectiveFOV"].as<float>());
					cc._camera.setPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
					cc._camera.setPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

					cc._camera.setOrthographicSize(cameraProps["OrthographicSize"].as<float>());
					cc._camera.setOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
					cc._camera.setOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());

					cc._primary = cameraComponent["Primary"].as<bool>();
					cc._fixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
				}

				auto spriteRendererComponent = entity["SpriteRendererComponent"];
				if (spriteRendererComponent)
				{
					auto& src = deserializedEntity.addComponent<SpriteRendererComponent>();
					src._color = spriteRendererComponent["Color"].as<glm::vec4>();
				}
            }
        }

        return true;
    }
    
    bool SceneSerializer::deserializeRunTime(const std::string& filepath) 
    {
        return false;
    }
}