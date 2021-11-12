#include "Actor.h"
#include "Manager.h"
#include <string.h>
#include "../../client/client/Macro.hpp"
#include "../../client/render/FileHandler.h"

GET_SET(state::Actor, int, HP)
GET_SET(state::Actor, int, AP)
GET_SET(state::Actor, int, MP)
GET_SET(state::Actor, int, DMG)
GET_SET(state::Actor, int, DEF)

state::Actor::Actor() : state::Manageable()
{
    HP(0);
    MP(0);
    AP(0);
    DMG(0);
    DEF(0);
}

state::Actor::Actor(std::vector<std::string> args) : state::Manageable(args[0], args[1])
{
    HP(std::stoi(args[2]));
    DMG(std::stoi(args[3]));
    DEF(std::stoi(args[4]));
    AP(std::stoi(args[5]));
    MP(std::stoi(args[6]));

    state::Manager::GetMgrByName("ACTOR_MGR")->Add(this);
    std::vector<std::string> s = render::FileHandler::SplitString(Name(), "_");
    if (!strcmp(s[0].c_str(), "BUILDING"))
    {
        if (!strcmp(s[1].c_str(), "MAUSOLEUM"))
            AssignPosition(2, 8);
        if (!strcmp(s[1].c_str(), "MAUSOLEUM2"))
            AssignPosition(22, 4);
        if (!strcmp(s[1].c_str(), "CYANKEEP"))
            AssignPosition(3, 8);
        if (!strcmp(s[1].c_str(), "CYANRESSOURCE"))
            AssignPosition(4, 8);
        if (!strcmp(s[1].c_str(), "REDKEEP"))
            AssignPosition(21, 4);
        if (!strcmp(s[1].c_str(), "REDRESSOURCE"))
            AssignPosition(20, 4);
    }
    if (!strcmp(s[0].c_str(), "HERO"))
    {
        //if(!strcmp(s[1].c_str(),"KNIGHT"))  AssignPosition(4,7);
        //if(!strcmp(s[1].c_str(),"CYANSWORDSMAN"))  AssignPosition(5,10);
        //if(!strcmp(s[1].c_str(),"REDSWORDSMAN"))  AssignPosition(19,6);
        if (!strcmp(s[1].c_str(), "CYANBOWMAN"))
            AssignPosition(3, 11);
        if (!strcmp(s[1].c_str(), "REDBOWMAN"))
            AssignPosition(20, 7);
        if (!strcmp(s[1].c_str(), "CYANMAGE"))
            AssignPosition(4, 9);
        if (!strcmp(s[1].c_str(), "REDMAGE"))
            AssignPosition(21, 5);
        if (!strcmp(s[1].c_str(), "CYANSPEARMAN"))
            AssignPosition(4, 10);
        if (!strcmp(s[1].c_str(), "REDSPEARMAN"))
            AssignPosition(21, 6);
        if (!strcmp(s[1].c_str(), "CYANKNIGHT"))
            AssignPosition(5, 11);
        if (!strcmp(s[1].c_str(), "REDKNIGHT"))
            AssignPosition(22, 7);
        if (!strcmp(s[1].c_str(), "CYANDRAGON"))
            AssignPosition(1, 7);
        if (!strcmp(s[1].c_str(), "REDDRAGON"))
            AssignPosition(23, 3);
    }
}

state::Actor::~Actor()
{
}