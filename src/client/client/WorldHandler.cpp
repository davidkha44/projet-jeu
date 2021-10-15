#include "WorldHandler.hpp"

void WorldHandler::OnTurnBegin()
{
    Turn((Turn()+1) % InputSources->size());
}

void WorldHandler::Event_Turn()
{

}
void WorldHandler::Event_CurrentWorld()
{
    for(Manager* m : Manager::Managers)
        m->Elements()->clear();
}