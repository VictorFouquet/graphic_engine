#pragma once

#include "camera.h"
#include "timestep.h"
#include "applicationEvent.h"
#include "mouseEvent.h"
#include "event.h"

namespace GraphicEngine
{

    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void onUpdate(Timestep timestep);
        void onEvent(Event& event);

        inline OrthographicCamera& getCamera() { return _camera; }

    private:
        bool onMouseScrolled(MouseScrolledEvent& e);
        bool onWindowResized(WindowResizeEvent& e);

        float _aspectRatio;
        float _zoomLevel = 1.0f;

        bool _rotation;

        float _cameraRotation = 0.0f;
        glm::vec3 _cameraPosition = { 0.0f, 0.0f, 0.0f };

        float _cameraTranslationSpeed = 2.0f;
        float _cameraRotationSpeed = 180.0f;

        OrthographicCamera _camera;
    };

}