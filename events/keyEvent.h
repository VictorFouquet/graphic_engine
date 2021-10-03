#pragma once

#include "event.h"

namespace GraphicEngine
{
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return _keyCode; }

        EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
    
    protected:
        KeyEvent(int keyCode)
            : _keyCode(keyCode) {}
        
        int _keyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), _repeatCount(repeatCount) {}
        
        inline int getRepeatCount() const { return _repeatCount; }
        
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent:" << _keyCode << "(" << _repeatCount << " repeats)";
            return ss.str();
        }

        //EVENT_CLASS_TYPE(keyPressed)
        static EventType getStaticType() { return EventType::keyPressed; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "KeyPressed"; }
    
    private:
        int _repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode)
            : KeyEvent(keyCode) {}

        std::string toString()
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << _keyCode;
            return ss.str();
        }

        // EVENT_CLASS_TYPE(keyReleased);
        static EventType getStaticType() { return EventType::keyReleased; }
        virtual EventType getEventType() const override { return getStaticType(); }
        virtual const char* getName() const override { return "KeyReleased"; }
    };
}
