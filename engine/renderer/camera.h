#pragma once

#include "glm/glm.hpp"


namespace GraphicEngine
{

    class Camera
    {
    public:
        Camera(const glm::mat4& projection)
            : _projection(projection) {}
        
        const glm::mat4& getProjection() const { return _projection; }
    private:
        glm::mat4 _projection;
    };

    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void setProjection(float left, float right, float bottom, float top);

        inline const glm::vec3& getPosition() const { return _position; }
        inline void setPosition(const glm::vec3& position) { _position = position; recalculateViewMatrix(); }

        inline float getRotation() const { return _rotation; }
        inline void setRotation(float rotation) { _rotation = rotation; recalculateViewMatrix(); }

        inline const glm::mat4& getProjectionMatrix() const { return _projectionMatrix; }
        inline const glm::mat4& getViewMatrix() const { return _viewMatrix; }
        inline const glm::mat4& getViewProjectionMatrix() const { return _viewProjectionMatrix; }
    private:
        void recalculateViewMatrix();

        glm::mat4 _projectionMatrix;
        glm::mat4 _viewMatrix;
        glm::mat4 _viewProjectionMatrix;

        glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
        float _rotation = 0.0f;
    };

}