#include "Macro.hpp"
#include "Handler.hpp"
#include "World.hpp"
#include "Manager.hpp"
#include "InputSource.hpp"

class WorldHandler : public Handler
{
    STATIC_EVENT(World*,CurrentWorld)
    STATIC_EVENT(int,Turn)
    STATIC(std::vector<InputSource>* InputSources)

    public :
        void OnTurnBegin() override;
    
    

    

    

};