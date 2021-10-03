#pragma once

#include "event.h"

namespace GraphicEngine
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : _width(width), _height(height) {}

        inline unsigned int getWidth() const { return _width; }
        inline unsigned int getHeight() const { return _height; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << _width << ", " << _height;

            return ss.str();
        }

        //EVENT_CLASS_TYPE(windowResize);
        static EventType getStaticType() { return EventType::windowResize; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "WindowResize"; }
        
        EVENT_CLASS_CATEGORY(eventCategoryApplication);
    private:
        unsigned int _width, _height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        //EVENT_CLASS_TYPE(windowClose);
        static EventType getStaticType() { return EventType::windowClose; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "WindowClose"; }
        
        EVENT_CLASS_CATEGORY(eventCategoryApplication);
    };
}