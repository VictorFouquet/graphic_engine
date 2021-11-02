#pragma once

#include <string>

namespace GraphicEngine
{

    class FileDialog
    {
    public:
        static std::string openFile(const char* filter);
        static std::string saveFile(const char* filter);
    };

}