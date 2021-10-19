#include "orthographicCameraController.h"
#include "precompiledHeaders.h"
#include "input.h"
#include "core.h"

namespace GraphicEngine
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : _aspectRatio(aspectRatio), _camera(-aspectRatio * _zoomLevel, aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel), _rotation(rotation)
    {
        
    }
    

    void OrthographicCameraController::onUpdate(Timestep timestep) 
    {
        // Handles mouse middle button pressed event to translate camera.
        if (Input::isMouseButtonPressed(2))
        {
            _cameraPosition.x += (std::get<0>(_latestMousePosition) - Input::getMouseX()) * timestep * _cameraTranslationSpeed * 0.15f;
            _cameraPosition.y -= (std::get<1>(_latestMousePosition) - Input::getMouseY()) * timestep * _cameraTranslationSpeed * 0.15f;
        }

        // Handles key pressed event to translate camera.
        if (Input::isKeyPressed(65))      // AZERTY Q - Move Left
        {
			_cameraPosition.x -= cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
			_cameraPosition.y -= sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
		}
        else if (Input::isKeyPressed(68)) // AZERTY D - Move Right
        {
			_cameraPosition.x += cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
			_cameraPosition.y += sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
		}
        if (Input::isKeyPressed(87))      // AZERTY Z - Move Up
        {
			_cameraPosition.x += -sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
			_cameraPosition.y += cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
		}
        else if (Input::isKeyPressed(83)) // AZERTY S - Move Down
        {
			_cameraPosition.x -= -sin(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
			_cameraPosition.y -= cos(glm::radians(_cameraRotation)) * _cameraTranslationSpeed * timestep;
		}

        // Handles key pressed event to rotate camera.
        if (_rotation)
        {
            if (Input::isKeyPressed(69))      // AZERTY A - AntiCW Rotation
                _cameraRotation -= _cameraRotationSpeed * timestep;
            else if (Input::isKeyPressed(81)) // AZERTY E - CW Rotation
                _cameraRotation += _cameraRotationSpeed * timestep;
            
            _camera.setRotation(_cameraRotation);
        }

        _camera.setPosition(_cameraPosition);
        _cameraTranslationSpeed = _zoomLevel;
        _latestMousePosition = { Input::getMouseX(), Input::getMouseY() };
    }
    
    void OrthographicCameraController::onEvent(Event& event) 
    {
        EventDispatcher dispatcher(event);

        dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }
    
    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) 
    {
        _zoomLevel -= e.getYOffset() * 0.25f;
        _zoomLevel = std::max(_zoomLevel, 0.25f);
        _camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);

        return false;
    }
    
    bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e) 
    {
        _aspectRatio = (float)e.getWidth() / (float)e.getHeight();
        _camera.setProjection(-_aspectRatio * _zoomLevel, _aspectRatio * _zoomLevel, -_zoomLevel, _zoomLevel);

        return false;
    }


}