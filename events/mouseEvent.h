#pragma once

#include "event.h"

namespace GraphicEngine
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : _mouseX(x), _mouseY(y) {}

        inline float getX() const { return _mouseX; }
        inline float getY() const { return _mouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;

            return ss.str();
        }

        // EVENT_CLASS_TYPE(mouseMoved);
        static EventType getStaticType() { return EventType::mouseMoved; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "MouseMoved"; }
        EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput);

    private:
        float _mouseX, _mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : _offsetX(xOffset), _offsetY(yOffset) {}

        inline float getXOffset() const { return _offsetX; }
        inline float getYOffset() const { return _offsetY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << getXOffset() << ", " << getYOffset();

            return ss.str();
        }

        // EVENT_CLASS_TYPE(mouseScrolled);
        static EventType getStaticType() { return EventType::mouseScrolled; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "MouseScrolled"; }
        EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput);
        
    private:
        float _offsetX, _offsetY;
    };

    class MouseButtonEvent : public Event
    {
    public:
      inline int getMouseButton() const { return _button; }

      EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput);      
    protected:
        MouseButtonEvent(int button)
            : _button(button) {}
        
        int _button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}
        
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << _button;
            
            return ss.str();
        }

        // EVENT_CLASS_TYPE(mouseButtonPressed);
        static EventType getStaticType() { return EventType::mouseButtonPressed; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "MouseButtonPressed"; }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}
        
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << _button;
            
            return ss.str();
        }

        // EVENT_CLASS_TYPE(mouseButtonReleased);
        static EventType getStaticType() { return EventType::mouseButtonReleased; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "MouseButtonReleased"; }
    };
}