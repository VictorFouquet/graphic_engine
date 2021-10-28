#pragma once

#include "camera.h"

namespace GraphicEngine
{

    class SceneCamera : public Camera
    {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void setOrthographic(float size, float nearClip, float farClip);
        void setViewportSize(uint32_t width, uint32_t height);

        float getOrthographicSize() const { return _orthographicSize; }
        void setOrthographicSize(float size) { _orthographicSize = size; recalculateProjection(); }
    private:
        void recalculateProjection();

    private:
        float _orthographicSize = 10.0f;
        float _orthographicNear = -1.0f, _orthographicFar = 1.0f;

        float _aspectRatio = 0.0f;
    };

}