#include "WorldHandler.h"
#include "Manager.h"
#include "../../client/render.h"
#include <iostream>

void state::WorldHandler::OnTurnBegin()
{
    Behaviour->RunFunction("OnTurnBegin",(int*)NULL);
    Turn = Behaviour->INT("TURN");
    std::cout << "ON_TURN_BEGIN_WH" << std::endl;
}
void state::WorldHandler::OnTurnBeginAsync()
{
    std::cout << "ON_TURN_BEGIN_ASYNC_WH" << std::endl;
}
void state::WorldHandler::OnTurnEnd()
{
    Behaviour->RunFunction("OnTurnEnd",(int*)NULL);
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

state::Player* state::WorldHandler::GetPlayerByName(std::string name)
{
    for(state::Player* p : Players)
    {
        if(p->Name() == name)
            return p;
    }
    return NULL;
}
state::Player* state::WorldHandler::GetPlayerByID(int id)
{
    for(state::Player* p : Players)
    {
        if(p->ID() == id)
            return p;
    }
    return NULL;
}

void state::WorldHandler::NetCommand(std::string cmd)
{
    std::vector<std::string> items = render::FileHandler::SplitString(cmd,":");
    std::vector<std::string> _s = render::FileHandler::SplitString(items[1],";");
    std::cout << _s[0] << "::" <<_s[1] << "::" << _s[2]  <<std::endl;
    int* args = (int*)malloc(_s.size()*sizeof(int));
    std::cout << "size" << _s.size() << std::endl;
    for(int i = 0; i < _s.size();i++)
    {
        
        args[i] = std::stol(_s[i],nullptr,16);
        std::cout << "s = " << args[i] << std::endl;
    }
    Behaviour->RunFunction(items[0],args);
    delete args;
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


