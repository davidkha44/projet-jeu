#include "Macro.hpp"
#include "Handler.hpp"
#include "World.hpp"
#include "Player.hpp"

class WorldHandler : public Handler
{
    STATIC(World* CurrentWorld)
    STATIC(int Turn)
    STATIC(std::vector<Player*>* Players)

    public :
        void OnTurnBegin() override;
    
    

    

    

};