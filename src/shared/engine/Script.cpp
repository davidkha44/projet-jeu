#include "Script.h"
#include "../../client/client/Macro.hpp"
#include "../../client/render.h"
#include "../state.h"



engine::Script::Script(std::vector<std::string> args)
{
    _Name = args[0];
    _ResPath = args[1];

    PARSE_BHV_SCRIPT(_ResPath, '#',_Text.push_back(line);)
    Scripts[_Name] = this;
}

int engine::Script::INT(std::string key)
{
    return _INTS[key];
}

void engine::Script::INT(std::string key,int value)
{
    _INTS[key] = value;
}
std::string engine::Script::STRING(std::string key)
{
    return _STRINGS[key];
}

void engine::Script::STRING(std::string key,std::string value)
{
    _STRINGS[key] = value;
}

void engine::Script::RunFunction(std::string func)
{
    bool begin_execution = false;
    std::cout << "EXEC " << func << std::endl;
    for(std::string line : _Text)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(line," ");
        if(items[0] == "END" && items[1] == "FUNCTION" && begin_execution) return;
        if(items[0] == "FUNCTION" && items[1] == func && !begin_execution) begin_execution = true;
        if(begin_execution) Run(line);
    }
}

void engine::Script::Run()
{
    bool inside_func = false;
    for(std::string line : _Text)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(line," ");
        if(inside_func)
        {
            if(items[0] == "END" && items[1] == "FUNCTION") inside_func = false;
        }
        else
        {
            if(items[0] == "FUNCTION") inside_func = true;
            Run(line);
        }
    }
}


void engine::Script::Run(std::string line)
{
    
    std::vector<std::string> items = render::FileHandler::SplitString(line," ");
    if(items[0] == "INT") _INTS[items[1]] = std::stoi(render::FileHandler::SplitString(line,"=")[1]);
    if(items[0] == "STRING") _STRINGS[items[1]] = render::FileHandler::SplitString(line,"=")[1];
    if(items[0] == "INC") _INTS[items[1]]++;
    if(items[0] == "DEC") _INTS[items[1]]--;
    if(items[0] == "PRINT_INT") std::cout << _INTS[items[1]] << std::endl;
    if(items[0] == "PRINT_STR") std::cout << _STRINGS[items[1]] << std::endl;
    if(items[0] == "ADD") 
    {
        char* p;
        int converted = (int)strtol(items[2].c_str(), &p, 10);
        (*p ? _INTS[items[1]] += _INTS[items[2]] : _INTS[items[1]] += converted);
    }
    if(items[0] == "MUL") 
    {
        char* p;
        int converted = (int)strtol(items[2].c_str(), &p, 10);
        (*p ? _INTS[items[1]] *= _INTS[items[2]] : _INTS[items[1]] *= converted);
    }
    if(items[0] == "SUB") 
    {
        char* p;
        int converted = (int)strtol(items[2].c_str(), &p, 10);
        (*p ? _INTS[items[1]] -= _INTS[items[2]] : _INTS[items[1]] -= converted);
    }
    if(items[0] == "DIV") 
    {
        char* p;
        int converted = (int)strtol(items[2].c_str(), &p, 10);
        (*p ? _INTS[items[1]] /= _INTS[items[2]] : _INTS[items[1]] /= converted);
    }
    if(items[0] == "MODULO") 
    {
        char* p;
        int converted = (int)strtol(items[2].c_str(), &p, 10);
        (*p ? _INTS[items[1]] %= _INTS[items[2]] : _INTS[items[1]] %= converted);
    }
    if(items[0] == "EQUAL") 
    {
        int f = 0;
        int s = 0;
        char* p1;
        char* p2;
        int converted_p1 = (int)strtol(items[1].c_str(), &p1, 10);
        int converted_p2 = (int)strtol(items[2].c_str(), &p2, 10);
        if(*p1)
        {
            if(items[1].find(".") != std::string::npos)
                f = ((state::Actor*)(state::Manager::GetMgrByName("ACTOR_MGR")->GetByName(render::FileHandler::SplitString(items[1],".")[0]).front()))->Property(render::FileHandler::SplitString(items[1],".")[1]);
            else
                f = _INTS[items[1]];
        }
        else
            f = converted_p1;
        if(*p2)
        {
            if(items[2].find(".") != std::string::npos)
                f = ((state::Actor*)(state::Manager::GetMgrByName("ACTOR_MGR")->GetByName(render::FileHandler::SplitString(items[2],".")[0]).front()))->Property(render::FileHandler::SplitString(items[2],".")[1]);
            else
                f = _INTS[items[2]];
        }
        else
            s = converted_p2;
        if(f == s) RunFunction(items[3]);

    }
    if(items[0] == "ACTOR")
    {
        char* p;
        char*px;
        char*py;
        int converted = (int)strtol(items[3].c_str(), &p, 10);
        int converted_px = (int)strtol(items[4].c_str(), &px, 10);
        int converted_py = (int)strtol(items[5].c_str(), &py, 10);
        std::vector<state::Actor*> _actors = render::FileHandler::DeserializeTable<state::Actor>("src/client/tables/Actors.csv","CSV");
        int x = 0;
        int y = 0;
        (*px ? x = _INTS[items[4]] : x = converted_px); 
        (*py ? y = _INTS[items[5]] : y = converted_py); 
        state::Actor* _actor = NULL;
        for(state::Actor* a : _actors)
        {
            if(a->Name() == items[2])
                _actor = a;
        }
        if(_actor)
        {
            _actor->Name(items[1]);
            _actor->AssignPosition(x,y);
        }
        (*p ? state::Manager::GetMgrByName(items[3])->Add(_actor) : state::Manager::GetMgrByID(converted)->Add(_actor));
    }
    if(items[0] == "ATTACH_PAWN")
    {
        int f = 0;
        int s = 0;
        char* p1;
        char* p2;
        int converted_p1 = (int)strtol(items[1].c_str(), &p1, 10);
        int converted_p2 = (int)strtol(items[2].c_str(), &p2, 10);
        (*p1 ? f = state::Manager::GetMgrByName("ACTOR_MGR")->GetByName(items[1]).front()->ID(): f = converted_p1);
        (*p2 ? s = state::WorldHandler::GetPlayerByName(items[2])->ID() : s = converted_p2);
        state::WorldHandler::GetPlayerByID(s)->AttachPawn((state::Actor*)state::Manager::GetMgrByName("ACTOR_MGR")->GetByID(f));
        
    }
    if(items[0] == "PLAYER")
    {
        state::WorldHandler::Players.push_back(new state::Player(items[1],(char)(std::stoi(items[2]) & 0xFF)));
    }
}