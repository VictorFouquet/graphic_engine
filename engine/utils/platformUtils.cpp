#include "precompiledHeaders.h"
#include "platformUtils.h"
#include "nfd.h"

namespace GraphicEngine
{

    std::string FileDialog::openFile(const char* filter)
    {
        NFD_Init();

        nfdchar_t *outPath;
        nfdfilteritem_t filterItem[1] = { { "Scene", filter } };
        nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
        if (result == NFD_OKAY)
        {
            std::string out(outPath);

            NFD_FreePath(outPath);

            NFD_Quit();

            return out;
        }

        NFD_Quit();
        
        return std::string();
    }

    std::string FileDialog::saveFile(const char* filter)
    {
        NFD_Init();

        nfdchar_t *outPath;
        nfdfilteritem_t filterItem[1] = { { "Scene", filter } };
         const nfdnchar_t* defaultName = "scene.algv";
        nfdresult_t result = NFD_SaveDialog(&outPath, filterItem, 1, NULL, defaultName);
        if (result == NFD_OKAY)
        {
            std::string out(outPath);

            NFD_FreePath(outPath);

            NFD_Quit();

            return out;
        }

        NFD_Quit();
        
        return std::string();
    }

}