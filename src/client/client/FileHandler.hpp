#include "Macro.hpp"
#include "Handler.hpp"
#include <vector>

class FileHandler : public Handler
{
    public :
        
        static void InitVisuals(std::string path);
        static void InitManagers(std::string path);
        static void InitWorld(std::string path);
        static std::vector<std::string> SplitString(std::string str,std::string separator);
};