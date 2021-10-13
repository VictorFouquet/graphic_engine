#pragma once

namespace GraphicEngine
{

    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            :_time(time)
        {
        }

        operator float() { return _time; } 

        float getSeconds() const { return _time; }
        float getMilliseconds() const { return _time * 1000.0f; }

    private:
        float _time;
    };

}