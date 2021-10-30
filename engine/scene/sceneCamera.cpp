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
        _projectionType = ProjectionType::Orthographic;

        _orthographicSize = size;
        _orthographicNear = nearClip;
        _orthographicFar = farClip;

        recalculateProjection();
    }
    
    void SceneCamera::setPerspective(float verticalFov, float nearClip, float farClip) 
    {
        _projectionType = ProjectionType::Perspective;

        _perspectiveFOV = verticalFov;
        _perspectiveNear = nearClip;
        _perspectiveFar = farClip;

        recalculateProjection();
    }
    
    void SceneCamera::setViewportSize(uint32_t width, uint32_t height) 
    {
        _aspectRatio = (float)width / (float)height;

        recalculateProjection();
    }
    
    void SceneCamera::recalculateProjection() 
    {
        if (_projectionType == ProjectionType::Perspective)
        {
            _projection = glm::perspective(_perspectiveFOV, _aspectRatio, _perspectiveNear, _perspectiveFar);
        }
        else if (_projectionType == ProjectionType::Orthographic)
        {
            float orthoLeft   = -_orthographicSize * 0.5f * _aspectRatio;
            float orthoRight  = _orthographicSize * 0.5f * _aspectRatio;
            float orthoBottom = -_orthographicSize * 0.5f;
            float orthoTop    = _orthographicSize * 0.5f;

            _projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, _orthographicNear, _orthographicFar);
        }
    }
}