#include "WorldHandler.h"
#include <iostream>

void State::WorldHandler::OnTurnBegin()
{
    Turn++;
    std::cout << "ON_TURN_BEGIN_WH" << std::endl;
}
void State::WorldHandler::OnTurnBeginAsync()
{
    std::cout << "ON_TURN_BEGIN_ASYNC_WH" << std::endl;
}
void State::WorldHandler::OnTurnEnd()
{
    std::cout << "ON_TURN_END_WH" << std::endl;
}
void State::WorldHandler::OnTurnEndAsync()
{
    std::cout << "ON_TURN_END_ASYNC_WH" << std::endl;
}

State::Player* State::WorldHandler::GetActivePlayer()
{
    return Players[Turn % Players.size()];
}
State::Player* State::WorldHandler::GetMyPlayer()
{
    return Players[MyID];
}

bool State::WorldHandler::IsOver()
{
    if(!((Status >> 4) ^ 0xF))
        return true;
    return false;

}
char State::WorldHandler::WinnerID()
{
    if(!IsOver())
        return -1;
    return Status & 0xF;
}



void State::WorldHandler::Initialize()
{
    CurrentWorld = NULL;
    Turn = 0;
    Instance = 0;
    Status = 0;
}
void State::WorldHandler::Initialize(World* w)
{
    CurrentWorld = w;
    Turn = 0;
    Instance = 0;
    Status = 0;
}

void* State::RunAsync(void* func)
{
    (*((std::function<void()>*)func))();
    return NULL;
}

template <class T> 
void State::WorldHandler::Suscribe2TurnBegin()
{
    TurnBeginEvents.push_back(T::OnTurnBegin);
}
template <class T> 
void State::WorldHandler::Suscribe2TurnBeginAsync()
{
    TurnBeginEvents.push_back(T::OnTurnBeginAsync);
}
template <class T> 
void State::WorldHandler::Suscribe2TurnEnd()
{
    TurnEndEvents.push_back(T::OnTurnEnd);
}
template <class T> 
void State::WorldHandler::Suscribe2TurnEndAsync()
{
    TurnEndEvents.push_back(T::OnTurnEndAsync);
}
