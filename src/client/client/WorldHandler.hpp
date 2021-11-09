#include "Macro.hpp"
#include "Handler.hpp"
#include "World.hpp"
#include "Manager.hpp"
#include "InputSource.hpp"

class WorldHandler 
{
    STATIC(World* CurrentWorld)
    STATIC(int Turn)
    STATIC(int MyID)
    STATIC(int Instance)
    STATIC(std::string FlushPath)
    STATIC(std::vector<InputSource*> InputSources)
    private : WorldHandler();
    public :
        static void OnTurnBegin();
        static void OnTurnBeginAsync();
        static void Flush2CSV();
        static InputSource* GetActiveInputSource();
        static InputSource* GetMyInputSource();

    
    

    

    

};