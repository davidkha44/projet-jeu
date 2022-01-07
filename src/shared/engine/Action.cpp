#include "Action.h"
#include "Pattern.h"
#include "../state.h"
#include "../../client/render.h"
#include "../../client/client/Macro.hpp"
#define COMMA ,

GET_SET(engine::Action, std::string, Name)
GET_SET(engine::Action, int, OPCode)
GET_SET(engine::Action, int, CostAP)
GET_SET(engine::Action, int, CostMP)
GET_SET(engine::Action, engine::Pattern *, BasePattern)
GET_SET(engine::Action, engine::NetCommand *, NetCmd)
GET_SET(engine::Action, bool, RequireRangeCheck)

engine::Action::Action(std::vector<std::string> args)
{
    _Name = args[0];
    _OPCode = std::stoi(args[1]);
    _CostAP = std::stoi(args[2]);
    _CostMP = std::stoi(args[3]);
    _BasePattern = Pattern::Patterns[args[4]];
    Actions[_Name] = this;
    _NetCmd = engine::NetCommand::NetCommands[args[5]];
    std::stoi(args[6]) ? _RequireRangeCheck = true : _RequireRangeCheck = false;
}

engine::Action *engine::Action::GetByNetCmd(std::string netcmd)
{
    std::vector<std::string> items = render::FileHandler::SplitString(netcmd, ":");
    PARSE_MAP(Actions, std::string, engine::Action *,

              if (it->second && render::FileHandler::SplitString(it->second->NetCmd()->Format().first, ":")[0] == items[0]) return it->second;)
    return NULL;
}
std::vector<sf::Vector2i> engine::Action::Reach(engine::Action *action, state::Actor *caster)
{
    std::vector<sf::Vector2i> output;
    for (state::Actor *a : action->BasePattern()->Map())
        output.push_back(VECTOR_ADD(caster->Position(),a->Position()));
    return output;
}
std::vector<state::Actor*> engine::Action::Vicinity(state::Actor *caster)
{
    std::vector<state::Actor*> output;
    for (state::Actor *a : BasePattern()->Map())
        if(state::Actor* a = (state::Actor*)state::Manager::GetMgrByName("ACTOR_MGR")->GetByPos(VECTOR_ADD(caster->Position(),a->Position())))
            output.push_back(a);        
    return output;
}
std::vector<state::Actor*> engine::Action::HostileVicinity(state::Actor *caster)
{
    std::vector<state::Actor*> output;
    for (state::Actor *a : BasePattern()->Map())
        if(state::Actor* a = (state::Actor*)state::Manager::GetMgrByName("ACTOR_MGR")->GetByPos(VECTOR_ADD(caster->Position(),a->Position())))
            if(a->Property("OWNER") != caster->Property("OWNER"))
                output.push_back(a);      
    return output;
}
std::vector<sf::Vector2i> engine::Action::Reach(engine::Action *action, int id)
{
    std::vector<sf::Vector2i> output;
    state::Actor* actor = (state::Actor*)state::Manager::GetMgrByName("ACTOR_MGR")->GetByID(id);
    return Reach(action,actor);
    
}

int engine::Action::IsInReach(int *args)
{
    state::Manager *mgr = state::Manager::GetMgrByID(args[0]);
    state::Actor *caster = (state::Actor *)mgr->GetByID(args[1]);
    state::Actor *target = (state::Actor *)mgr->GetByPos(args[2], args[3]);

    Action *action;
    PARSE_MAP(Actions, std::string, Action *,
    if (it->second && it->second->OPCode() == args[4])
        action = it->second;)
    for (sf::Vector2i v : Reach(action, caster))
        if (target && target->Position().x == v.x && target->Position().y == v.y)
            return 1;
    return 0;
}

engine::Action::Action(std::string args) 
{

}