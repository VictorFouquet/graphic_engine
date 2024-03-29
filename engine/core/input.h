#pragma once

#include "precompiledHeaders.h"
#include "core.h"

namespace GraphicEngine
{
    class Input
    {
    public:
		Input() = default;
        virtual ~Input() = default;

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
        
        inline static bool        isKeyPressed(int keycode)        { return _instance->isKeyPressedImpl(keycode); };

        inline static bool        isMouseButtonPressed(int button) { return _instance->isMouseButtonPressedImpl(button); };
        
        inline static float       getMouseX()                      { return _instance->getMouseXImpl(); };
        inline static float       getMouseY()                      { return _instance->getMouseYImpl(); };
        
        inline static std::pair
            <float, float>        getMousePosition()               { return _instance->getMousePositionImpl(); };
        
        static Scope<Input> Create();
    protected:
        bool  isKeyPressedImpl(int keycode);
        bool  isMouseButtonPressedImpl(int button);
        float getMouseXImpl();
        float getMouseYImpl();
        std::pair<float, float> getMousePositionImpl();
    
    private:
        static Scope<Input> _instance;
    };
} // namespace GrapichEngine
