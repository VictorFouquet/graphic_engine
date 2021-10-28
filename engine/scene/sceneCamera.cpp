#include "glm/gtc/matrix_transform.hpp"

#include "precompiledHeaders.h"
#include "sceneCamera.h"

namespace GraphicEngine
{
    SceneCamera::SceneCamera() 
    {
        recalculateProjection();
    }
    
    void SceneCamera::setOrthographic(float size, float nearClip, float farClip) 
    {
        _orthographicSize = size;
        _orthographicNear = nearClip;
        _orthographicFar = farClip;

        recalculateProjection();
    }
    
    void SceneCamera::setViewportSize(uint32_t width, uint32_t height) 
    {
        _aspectRatio = (float)width / (float)height;

        recalculateProjection();
    }
    
    void SceneCamera::recalculateProjection() 
    {
        float orthoLeft   = -_orthographicSize * 0.5f * _aspectRatio;
        float orthoRight  = _orthographicSize * 0.5f * _aspectRatio;
        float orthoBottom = -_orthographicSize * 0.5f;
        float orthoTop    = _orthographicSize * 0.5f;

        _projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, _orthographicNear, _orthographicFar);
    }
}