#include "Script.h"
#include "SelectionHandler.h"
#include "../../client/client/Macro.hpp"
#include "../../client/render.h"
#include "../state.h"



engine::Script::Script(std::vector<std::string> args)
{
    _Name = args[0];
    _ResPath = args[1];
    _INTS["RESERVED:JMP"] = 0;
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
void engine::Script::RegisterNetVar(std::string key,state::Actor* actor)
{
    _NET_VARS[key] = actor;
}
int engine::Script::EvaluateINT(std::string str,int* args)
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
        if(items[0] == "NET_VAR")
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[1],".");
            result = ((state::Actor*)_NET_VARS[_items[0]])->Property(_items[1]);
        }
    }
    if(str.find("::") != std::string::npos)
    {
        std::vector<std::string> _items = render::FileHandler::SplitString(str,"::");
        std::vector<std::string> __items = render::FileHandler::SplitString(_items[1],".");
        result = ((state::Actor*)state::Manager::GetMgrByName(_items[0])->GetByID(EvaluateINT(__items[0],args)))->GetNetParam(__items[1]);
    

    }
    else if(str.find(".") != std::string::npos)
    {
        result = ((state::Actor*)(state::Manager::GetMgrByName("ACTOR_MGR")->GetByName(render::FileHandler::SplitString(str,".")[0]).front()))->Property(render::FileHandler::SplitString(str,".")[1]);
    }
    else if(str.find("ARGS:") != std::string::npos)
    {
        result = args[std::stoi(render::FileHandler::SplitString(str,":")[1])];
    }
    else
    {
        char* p;
        int converted = (int)strtol(str.c_str(), &p, 10);
        (*p ? result = _INTS[str] : result = converted);
    }

    return result;
}

void engine::Script::RunFunction(std::string func,int* args)
{
    if(func.find("::") != std::string::npos)
    {
       std::vector<std::string> items = render::FileHandler::SplitString(func,"::"); 
       if(items[0] == "FUNC")
       {
           _INTS["RET:"+items[1]] = STATIC_FUNCTIONS[items[1]](args);
           return;
       }
    }
    bool begin_execution = false;
    std::cout << "EXEC " << func << std::endl;
    for(std::string line : _Text)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(line," ");
        if(items[0] == "END" && items[1] == "FUNCTION" && begin_execution) return;
        if(begin_execution)
        {
            if(items[0] == "RETURN")
            {
                if(items[1] == "INT") _INTS["RET:"+func] = EvaluateINT(items[2],args);
                if(items[1] == "STRING") _STRINGS["RET:"+func] = items[2];
            }
            else if(_INTS["RESERVED:JMP"])
            {
                _INTS["RESERVED:JMP"]--;
                continue;
            }
            else Run(line,args);
        } 
        if(items[0] == "FUNCTION" && items[1] == func && !begin_execution) begin_execution = true;
    }
}
void engine::Script::RunFunction(std::string func,int argcount)
{
    int* ARGS = (int*)calloc(argcount,sizeof(int));
    while(--argcount >= 0)
    {
        ARGS[argcount] = _Stack.top();
        _Stack.pop();
    }
    RunFunction(func,ARGS);
    delete ARGS;
}
void engine::Script::RunKey(std::string key)
{
    bool begin_execution = false;
    std::cout << "EXEC KEY " << key << std::endl;
    for(std::string line : _Text)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(line," ");
        if(items[0] == "END" && items[1] == "KEY" && begin_execution) return;
        if(begin_execution) Run(line,(int*)NULL);
        if(items[0] == "KEY" && items[1] == key && !begin_execution) begin_execution = true;
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
            if(_INTS["RESERVED:JMP"])
            {
                _INTS["RESERVED:JMP"]--;
                continue;
            }
            Run(line,(int*)NULL);
        }
    }
}


void engine::Script::Run(std::string line,int* args)
{
    //std::cout << _Name <<"::LINE : " << line << std::endl;
    std::vector<std::string> items = render::FileHandler::SplitString(line," ");
    if(items[0] == "INT") _INTS[items[1]] = EvaluateINT(render::FileHandler::SplitString(line,"=")[1],args);
    if(items[0] == "STRING") _STRINGS[items[1]] = render::FileHandler::SplitString(line,"=")[1];
    if(items[0] == "INC") _INTS[items[1]]++;
    if(items[0] == "DEC") _INTS[items[1]]--;
    if(items[0] == "PRINT_INT") std::cout << EvaluateINT(items[1],args) << std::endl;
    if(items[0] == "PRINT_STR") std::cout << _STRINGS[items[1]] << std::endl;
    if(items[0] == "ADD")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] += EvaluateINT(items[2],args) :
        _INTS[items[1]] += EvaluateINT(items[2],args);
    } 
    if(items[0] == "SUB")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] -= EvaluateINT(items[2],args) :
        _INTS[items[1]] -= EvaluateINT(items[2],args);
    } 
    if(items[0] == "MODULO")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] %= EvaluateINT(items[2],args) :
        _INTS[items[1]] %= EvaluateINT(items[2],args);
    } 
    if(items[0] == "MUL")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] *= EvaluateINT(items[2],args) :
        _INTS[items[1]] *= EvaluateINT(items[2],args);
    } 
    if(items[0] == "DIV")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] /= EvaluateINT(items[2],args) :
        _INTS[items[1]] /= EvaluateINT(items[2],args);
    } 
    if(items[0] == "XOR")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] ^= EvaluateINT(items[2],args) :
        _INTS[items[1]] ^= EvaluateINT(items[2],args);
    } 
    if(items[0] == "AND")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] &= EvaluateINT(items[2],args) :
        _INTS[items[1]] &= EvaluateINT(items[2],args);
    } 
    if(items[0] == "OR")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] |= EvaluateINT(items[2],args) :
        _INTS[items[1]] |= EvaluateINT(items[2],args);
    } 
    if(items[0] == "RBS")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] >>= EvaluateINT(items[2],args) :
        _INTS[items[1]] >>= EvaluateINT(items[2],args);
    }
    if(items[0] == "LBS")
    {
        items[1].find("ARGS:") != std::string::npos ? 
        args[std::stoi(render::FileHandler::SplitString(items[1],":")[1])] <<= EvaluateINT(items[2],args) :
        _INTS[items[1]] <<= EvaluateINT(items[2],args);
    } 


    //if(items[0] == "EQUAL" && EvaluateINT(items[1],args) == EvaluateINT(items[2],args)) RunFunction(items[3],(int*)NULL);
    if(items[0] == "EQUAL" && EvaluateINT(items[1],args) == EvaluateINT(items[2],args))
    {
        if(items[3].find("JMP:") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[3],":");
            _INTS["RESERVED:JMP"] = std::stoi(_items[1]);
            return;
        }
        else RunFunction(items[3],(int*)NULL);
    }
    if(items[0] == "NEQUAL" && EvaluateINT(items[1],args) != EvaluateINT(items[2],args))
    {
        if(items[3].find("JMP:") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[3],":");
            _INTS["RESERVED:JMP"] = std::stoi(_items[1]);
            return;
        }
        else RunFunction(items[3],(int*)NULL);
    }
    if(items[0] == "GT" && EvaluateINT(items[1],args) > EvaluateINT(items[2],args))
    {
        if(items[3].find("JMP:") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[3],":");
            _INTS["RESERVED:JMP"] = std::stoi(_items[1]);
            return;
        }
        else RunFunction(items[3],(int*)NULL);
    }
    if(items[0] == "GTE" && EvaluateINT(items[1],args) >= EvaluateINT(items[2],args))
    {
        if(items[3].find("JMP:") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[3],":");
            _INTS["RESERVED:JMP"] = std::stoi(_items[1]);
            return;
        }
        else RunFunction(items[3],(int*)NULL);
    } 
    if(items[0] == "LT" && EvaluateINT(items[1],args) < EvaluateINT(items[2],args))
    {
        if(items[3].find("JMP:") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[3],":");
            _INTS["RESERVED:JMP"] = std::stoi(_items[1]);
            return;
        }
        else RunFunction(items[3],(int*)NULL);
    }
    if(items[0] == "LTE" && EvaluateINT(items[1],args) <= EvaluateINT(items[2],args))
    {
        if(items[3].find("JMP:") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[3],":");
            _INTS["RESERVED:JMP"] = std::stoi(_items[1]);
            return;
        }
        else RunFunction(items[3],(int*)NULL);
    }
    //if(items[0] == "NEQUAL" && EvaluateINT(items[1],args) != EvaluateINT(items[2],args)) RunFunction(items[3],(int*)NULL);
    //if(items[0] == "GT" && EvaluateINT(items[1],args) > EvaluateINT(items[2],args)) RunFunction(items[3],(int*)NULL);
    //if(items[0] == "GTE" && EvaluateINT(items[1],args) >= EvaluateINT(items[2],args)) RunFunction(items[3],(int*)NULL);
    //if(items[0] == "LT" && EvaluateINT(items[1],args) < EvaluateINT(items[2],args)) RunFunction(items[3],(int*)NULL);
    //if(items[0] == "LTE" && EvaluateINT(items[1],args) <= EvaluateINT(items[2],args)) RunFunction(items[3],(int*)NULL);

    if(items[0] == "ACTOR")
    {
        int x = EvaluateINT(items[4],args);
        int y = EvaluateINT(items[5],args);
        
        std::vector<state::Actor*> _actors = render::FileHandler::DeserializeTable<state::Actor>("src/client/tables/Actors.csv","CSV");
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
        state::Manager::GetMgrByName(items[3])->Add(_actor);
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
        state::WorldHandler::Players.push_back(new state::Player(items[1],(char)(std::stoi(items[2]) & 0xFF),Scripts[items[3]]));
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
                if(__items[1] == "ACTION") {((state::Actor*)engine::SelectionHandler::FilteredSelection[__items[0]])->ChangeAction(items[2]);return;}
                else ((state::Actor*)engine::SelectionHandler::FilteredSelection[__items[0]])->Property(__items[1],EvaluateINT(items[2],args));
            }
            if(_items[0] == "NET_VAR")
            {
                std::vector<std::string> __items = render::FileHandler::SplitString(_items[1],".");
                _NET_VARS[__items[0]]->Property(__items[1],EvaluateINT(items[2],args));
            }
            else
            {
               std::vector<std::string> __items = render::FileHandler::SplitString(_items[1],".");
               ((state::Actor*)state::Manager::GetMgrByName(_items[0])->GetByName(__items[0]).front())->Property(__items[1],EvaluateINT(items[2],args));
            }
        }
        if(items[1].find("::") != std::string::npos)
        {
            std::vector<std::string> _items = render::FileHandler::SplitString(items[1],"::");
            std::vector<std::string> __items = render::FileHandler::SplitString(_items[1],".");
            ((state::Actor*)state::Manager::GetMgrByName(_items[0])->GetByID(EvaluateINT(__items[0],args)))->Property(__items[1],EvaluateINT(items[2],args));
        }
    }
    if(items[0] == "CALL")
    {
        if(items.size() > 2)
        {
            for(int i = 2; i < items.size();i++)
                _Stack.push(EvaluateINT(items[i],args));
            RunFunction(items[1],items.size() - 2);
        }
        else RunFunction(items[1],(int*)NULL);
    }
}