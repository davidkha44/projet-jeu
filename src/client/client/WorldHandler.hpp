#include "Macro.hpp"
#include "Handler.hpp"
#include "World.hpp"
#include "Manager.hpp"
#include "InputSource.hpp"

class WorldHandler 
{
    STATIC_EVENT(World*, CurrentWorld)
    STATIC(int Turn)
    STATIC(int Instance)
    STATIC(std::string FlushPath)
    STATIC(std::vector<InputSource>* InputSources)
    private : WorldHandler();
    public :
        static void OnTurnBegin();
        static void OnTurnBeginAsync();
        static void Flush2CSV();
    
    

    

    

};