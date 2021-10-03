#pragma once

#include "precompiledHeaders.h"

#define BIT(x) (1 << x)

namespace GraphicEngine
{
    enum class EventType
    {
        none = 0,
        windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
        appTick, appUpdate, appRender,
        keyPressed, keyReleased,
        mouseButtonPressed, mouseButtonReleased, mouseMoved, mouseScrolled 
    };

    enum EventCategory
    {
        none = 0,
        eventCategoryApplication = BIT(0),
        eventCategoryInput       = BIT(1),
        eventCategoryKeyboard    = BIT(2),
        eventCategoryMouse       = BIT(3),
        eventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
                                virtual EventType getEventType() const override { return getStaticType(); }\
                                virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    class Event
    {
        friend class EventDispatcher;

    public:
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category)
        {
            return getCategoryFlags() & category;
        }
    
    protected:
        bool handled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : _Event(event)
        {
        }

        template<typename T>
        bool dispatch(EventFn<T> func)
        {
            if (_Event.getEventType() == T::getStaticType())
            {
                _Event.handled = func(*(T*)&_Event);
                return true;
            }
            return false;
        }

    private:
        Event& _Event;
    };
    
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.toString();
    }
} // namespace GraphicEngine
