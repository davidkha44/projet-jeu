#include "Action.h"
#include "Pattern.h"
#include "../../client/client/Macro.hpp"

GET_SET(engine::Action,std::string,Name)
GET_SET(engine::Action,int,OPCode)
GET_SET(engine::Action,int,CostAP)
GET_SET(engine::Action,int,CostMP)
GET_SET(engine::Action,engine::Pattern*,BasePattern)


engine::Action::Action(std::vector<std::string> args)
{
    _Name = args[0];
    _OPCode = std::stoi(args[1]);
    _CostAP = std::stoi(args[2]);
    _CostMP = std::stoi(args[3]);
    _BasePattern = Pattern::Patterns[args[4]];
    Actions[_Name] = this;
}

