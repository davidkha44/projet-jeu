#include "WorldHandler.h"
#include <iostream>

void state::WorldHandler::OnTurnBegin()
{
    Turn++;
    std::cout << "ON_TURN_BEGIN_WH" << std::endl;
}
void state::WorldHandler::OnTurnBeginAsync()
{
    std::cout << "ON_TURN_BEGIN_ASYNC_WH" << std::endl;
}
void state::WorldHandler::OnTurnEnd()
{
    std::cout << "ON_TURN_END_WH" << std::endl;
}
void state::WorldHandler::OnTurnEndAsync()
{
    std::cout << "ON_TURN_END_ASYNC_WH" << std::endl;
}

state::Player* state::WorldHandler::GetActivePlayer()
{
    return Players[Turn % Players.size()];
}
state::Player* state::WorldHandler::GetMyPlayer()
{
    return Players[MyID];
}

bool state::WorldHandler::IsOver()
{
    if(!((Status >> 4) ^ 0xF))
        return true;
    return false;

}
char state::WorldHandler::WinnerID()
{
    if(!IsOver())
        return -1;
    return Status & 0xF;
}



void state::WorldHandler::Initialize()
{
    CurrentWorld = NULL;
    Turn = 0;
    Instance = 0;
    Status = 0;
}
void state::WorldHandler::Initialize(World* w)
{
    CurrentWorld = w;
    Turn = 0;
    Instance = 0;
    Status = 0;
}

void* state::WorldHandler::RunAsync(void* func)
{
    (*((std::function<void()>*)func))();
    return NULL;
}

template <class T> 
void state::WorldHandler::Subscribe2TurnBegin()
{
    TurnBeginEvents.push_back(T::OnTurnBegin);
}
template <class T> 
void state::WorldHandler::Subscribe2TurnBeginAsync()
{
    TurnBeginEvents.push_back(T::OnTurnBeginAsync);
}
template <class T> 
void state::WorldHandler::Subscribe2TurnEnd()
{
    TurnEndEvents.push_back(T::OnTurnEnd);
}
template <class T> 
void state::WorldHandler::Subscribe2TurnEndAsync()
{
    TurnEndEvents.push_back(T::OnTurnEndAsync);
}


