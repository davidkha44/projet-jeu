#include "Action.h"
#include "Pattern.h"
#include "../state.h"
#include "../../client/render.h"
#include "../../client/client/Macro.hpp"
#define COMMA ,

GET_SET(engine::Action,std::string,Name)
GET_SET(engine::Action,int,OPCode)
GET_SET(engine::Action,int,CostAP)
GET_SET(engine::Action,int,CostMP)
GET_SET(engine::Action,engine::Pattern*,BasePattern)
GET_SET(engine::Action,engine::NetCommand*,NetCmd)


engine::Action::Action(std::vector<std::string> args)
{
    _Name = args[0];
    _OPCode = std::stoi(args[1]);
    _CostAP = std::stoi(args[2]);
    _CostMP = std::stoi(args[3]);
    _BasePattern = Pattern::Patterns[args[4]];
    Actions[_Name] = this;
    _NetCmd = engine::NetCommand::NetCommands[args[5]];
}

engine::Action* engine::Action::CheckRange(std::string netcmd,int* args)
{
    std::vector<std::string> items = render::FileHandler::SplitString(netcmd,":");
    PARSE_MAP(Actions,std::string,engine::Action*,

    if(it->second && render::FileHandler::SplitString(it->second->NetCmd()->Format().first,":")[0] == items[0])
    {
        std::vector<sf::Vector2i> PossiblePos;
        for(state::Actor* a : it->second->BasePattern()->Map())
        {
            int _x = 0;
            int _y = 0;
            _x += state::Manager::GetMgrByName("ACTOR_MGR")->GetByID(args[0])->Position().x + a->Position().x;
            _y += state::Manager::GetMgrByName("ACTOR_MGR")->GetByID(args[0])->Position().y + a->Position().y;
            if(_x == args[1] && _y == args[2])
                return it->second;
        }
    } 
    )
    return NULL;
}