#include "WorldHandler.hpp"
#include <fstream>
#include <iostream>

void WorldHandler::OnTurnBegin()
{
    Flush();
    std::cout << "ON_TURN_BEGIN_WH" << std::endl;

}
void WorldHandler::OnTurnBeginAsync()
{
    
    std::cout << "ON_TURN_BEGIN_ASYNC_WH" << std::endl;
}


void WorldHandler::Event_Turn()
{

}
void WorldHandler::Event_CurrentWorld()
{

}

void WorldHandler::Flush()
{
    PRINTLN("FLUSH START")
   for(Manager* m : Manager::Managers)
   {
       std::cout << m->Name() << std::endl;
        m->Flush(0,0);
   }
    PRINTLN("FLUSH DONE")
    
}


