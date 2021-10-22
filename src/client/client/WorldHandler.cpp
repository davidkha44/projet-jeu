#include "WorldHandler.hpp"
#include <fstream>
#include <iostream>

void WorldHandler::OnTurnBegin()
{
    Turn++;
    std::cout << "ON_TURN_BEGIN_WH" << std::endl;
}
void WorldHandler::OnTurnBeginAsync()
{
    //Flush2CSV();
    std::cout << "ON_TURN_BEGIN_ASYNC_WH" << std::endl;
}

InputSource* WorldHandler::GetActiveInputSource()
{
    return InputSources[Turn % InputSources.size()];
}
InputSource* WorldHandler::GetMyInputSource()
{
    return InputSources[MyID];
}

void WorldHandler::Event_CurrentWorld()
{

}

void WorldHandler::Flush2CSV()
{
    PRINTLN("FLUSH START")

   for(Manager* m : Manager::Managers)
   {
       if(m->Flush())
        {
            std::cout << m->Name() << std::endl;
            m->Flush2CSV(0,Turn);
        }
   }
    PRINTLN("FLUSH DONE")
    
}


