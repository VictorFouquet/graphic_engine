#pragma once

#include "camera.h"

namespace GraphicEngine
{

    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType
        {
            Perspective = 0,
            Orthographic = 1
        };

    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void setViewportSize(uint32_t width, uint32_t height);

        void setOrthographic(float size, float nearClip, float farClip);
        void setPerspective(float verticalFov, float nearClip, float farClip);

        float getPerspectiveVericalFOV() const { return _perspectiveFOV; }
        void setPerspectiveVericalFOV(float verticalFov) { _perspectiveFOV = verticalFov; recalculateProjection(); }
        float getPerspectiveNearClip() const { return _perspectiveNear; }
        void setPerspectiveNearClip(float clip) { _perspectiveNear = clip; recalculateProjection(); }
        float getPerspectiveFarClip() const { return _perspectiveFar; }
        void setPerspectiveFarClip(float clip) { _perspectiveFar = clip; recalculateProjection(); }

        float getOrthographicSize() const { return _orthographicSize; }
        void setOrthographicSize(float size) { _orthographicSize = size; recalculateProjection(); }
        float getOrthographicNearClip() const { return _orthographicNear; }
        void setOrthographicNearClip(float clip) { _orthographicNear = clip; recalculateProjection(); }
        float getOrthographicFarClip() const { return _orthographicFar; }
        void setOrthographicFarClip(float clip) { _orthographicFar = clip; recalculateProjection(); }

        ProjectionType getProjectionType() const { return _projectionType; }
        void setProjectionType(ProjectionType type) { _projectionType = type; recalculateProjection(); }

    private:
        void recalculateProjection();

    private:
        ProjectionType _projectionType = ProjectionType::Orthographic;

        float _perspectiveFOV = glm::radians(45.0f);
        float _perspectiveNear = 0.01f, _perspectiveFar = 1000.0f;

        float _orthographicSize = 10.0f;
        float _orthographicNear = -1.0f, _orthographicFar = 1.0f;

        float _aspectRatio = 0.0f;
    };

}