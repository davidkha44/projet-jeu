#include "Macro.hpp"
#include "SelectionHandler.hpp"
#include <vector>
#include "MainFrame.hpp"
class FileHandler
{
    public :
        
        static void InitVisuals(std::string path);
        static void InitActors(std::string path);
        static void InitManagers(std::string path);
        static MainFrame* InitWorlds(std::string path,std::string wname);
        static void InitWorld(std::string path,int csx,int csy,int ncx,int ncy);
        static void InitArgs(MainFrame* mf,std::string path);
        static std::vector<std::string> SplitString(std::string str,std::string separator);
};