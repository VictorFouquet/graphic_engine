#include "camera.h"

#include "precompiledHeaders.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GraphicEngine
{

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : _projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(1.0f)
    {
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }
    
    void OrthographicCamera::recalculateViewMatrix() 
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

        _viewMatrix = glm::inverse(transform);
        _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
    }

}
