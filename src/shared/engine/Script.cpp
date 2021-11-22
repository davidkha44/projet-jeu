#include "Script.h"
#include "SelectionHandler.h"
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
int engine::Script::EvaluateINT(std::string str)
{
    int result = 0;
    if(str.find("->") != std::string::npos)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(str,"->");
        if(items[0] == "FILTERED_SELECTION")
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[1],".");
            result = ((state::Actor*)engine::SelectionHandler::FilteredSelection[_items[0]])->Property(_items[1]);
        }

    }
    else if(str.find(".") != std::string::npos)
    {
        result = ((state::Actor*)(state::Manager::GetMgrByName("ACTOR_MGR")->GetByName(render::FileHandler::SplitString(str,".")[0]).front()))->Property(render::FileHandler::SplitString(str,".")[1]);
    }
    else
    {
        char* p;
        int converted = (int)strtol(str.c_str(), &p, 10);
        (*p ? result = _INTS[str] : result = converted);
    }

    return result;
}

void engine::Script::RunFunction(std::string func)
{
    bool begin_execution = false;
    std::cout << "EXEC " << func << std::endl;
    for(std::string line : _Text)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(line," ");
        if(items[0] == "END" && items[1] == "FUNCTION" && begin_execution) return;
        if(begin_execution) Run(line);
        if(items[0] == "FUNCTION" && items[1] == func && !begin_execution) begin_execution = true;
    }
}
void engine::Script::RunSelectionMask(std::string sm)
{

    engine::SelectionHandler::SelectionMask.clear();
    bool begin_execution = false;
    std::cout << "EXEC SM " << sm << std::endl;
    for(std::string line : _Text)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(line," ");
        if(items[0] == "END" && items[1] == "SELECTION_MASK" && begin_execution) return;
        if(begin_execution)
        {
            if(items[0] == "DEFAULT") 
            {
                engine::SelectionHandler::SelectionMask.push_back(line);
                engine::SelectionHandler::SelectionState = items[1];
            }

            else engine::SelectionHandler::SelectionMask.push_back(line);
            
        }
        if(items[0] == "SELECTION_MASK" && items[1] == sm && !begin_execution) begin_execution = true;
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
    if(items[0] == "INT") _INTS[items[1]] = EvaluateINT(render::FileHandler::SplitString(line,"=")[1]);
    if(items[0] == "STRING") _STRINGS[items[1]] = render::FileHandler::SplitString(line,"=")[1];
    if(items[0] == "INC") _INTS[items[1]]++;
    if(items[0] == "DEC") _INTS[items[1]]--;
    if(items[0] == "PRINT_INT") std::cout << EvaluateINT(items[1]) << std::endl;
    if(items[0] == "PRINT_STR") std::cout << _STRINGS[items[1]] << std::endl;
    if(items[0] == "ADD") _INTS[items[1]] += EvaluateINT(items[2]);
    if(items[0] == "SUB") _INTS[items[1]] -= EvaluateINT(items[2]);
    if(items[0] == "MUL") _INTS[items[1]] *= EvaluateINT(items[2]);
    if(items[0] == "DIV") _INTS[items[1]] /= EvaluateINT(items[2]);
    if(items[0] == "XOR") _INTS[items[1]] ^= EvaluateINT(items[2]);
    if(items[0] == "AND") _INTS[items[1]] &= EvaluateINT(items[2]);
    if(items[0] == "OR") _INTS[items[1]] |= EvaluateINT(items[2]);
    if(items[0] == "RBS") _INTS[items[1]] >>= EvaluateINT(items[2]);
    if(items[0] == "LBS") _INTS[items[1]] <<= EvaluateINT(items[2]);

    if(items[0] == "EQUAL" && EvaluateINT(items[1]) == EvaluateINT(items[2])) RunFunction(items[3]);
    if(items[0] == "NEQUAL" && EvaluateINT(items[1]) != EvaluateINT(items[2])) RunFunction(items[3]);
    if(items[0] == "GT" && EvaluateINT(items[1]) > EvaluateINT(items[2])) RunFunction(items[3]);
    if(items[0] == "GTE" && EvaluateINT(items[1]) >= EvaluateINT(items[2])) RunFunction(items[3]);
    if(items[0] == "LT" && EvaluateINT(items[1]) < EvaluateINT(items[2])) RunFunction(items[3]);
    if(items[0] == "LTE" && EvaluateINT(items[1]) <= EvaluateINT(items[2])) RunFunction(items[3]);

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
    if(items[0] == "SELECTION_MASK")
    {
        RunSelectionMask(items[1]);
    }
    if(items[0] == "PROPERTY")
    {
        if(items[1].find("->") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[1],"->");
            if(_items[0] == "FILTERED_SELECTION")
            {
                std::vector<std::string> __items = render::FileHandler::SplitString(_items[1],".");
                ((state::Actor*)engine::SelectionHandler::FilteredSelection[__items[0]])->Property(__items[1],EvaluateINT(items[2]));
            }
            else
            {
               std::vector<std::string> __items = render::FileHandler::SplitString(_items[1],".");
               ((state::Actor*)state::Manager::GetMgrByName(_items[0])->GetByName(__items[0]).front())->Property(__items[1],EvaluateINT(items[2]));
            }
        }
    }
}