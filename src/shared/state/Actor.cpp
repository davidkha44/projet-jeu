#include "Actor.h"
#include "Manager.h"
#include <string.h>
#include "../../client/client/Macro.hpp"
#include "../engine.h"
#define COMMA ,

GET_SET(state::Actor, std::map<std::string COMMA int>, Properties)
GET_SET(state::Actor, std::string,CurrentAction)


state::Actor::Actor() : state::Manageable()
{
    _Properties["HP"] = 0;
    _Properties["DMG"] = 0;
    _Properties["DEF"] = 0;
    _Properties["AP"] = 0;
    _Properties["MP"] = 0;

}

state::Actor::Actor(std::vector<std::string> args) : state::Manageable(args[0], args[1])
{
    _Properties["HP"] = std::stoi(args[2]);
    _Properties["DMG"] = std::stoi(args[3]);
    _Properties["DEF"] = std::stoi(args[4]);
    _Properties["AP"] = std::stoi(args[5]);
    _Properties["MP"] = std::stoi(args[6]);
    ID(ID()+ state::Manager::GetMgrByName("ACTOR_MGR")->Elements().size());
    std::vector<std::string> _actions = engine::FileHandler::SplitString(args[7],";");
    _CurrentAction = _actions[0];
    if(_actions.size())
    {
        for(std::string s : _actions)
            _Actions[s] = engine::Action::Actions[s];
    }

}

state::Actor::Actor(std::string args) : state::Manageable(args)
{
    /*
        Example : 
        Name=build_mausoleum2,ID=03E90000,ACTION=STD_INVOKE,AP=100,DEF=60,DMG=30,HP=100,MP=0,OWNER=0,X=5,Y=8
    */
    for(std::string str : engine::FileHandler::SplitString(args,","))
    {
        std::vector<std::string> prop = engine::FileHandler::SplitString(str,"=");
        if(prop[0] == "ACTION")
        {
            std::vector<std::string> _actions = engine::FileHandler::SplitString(prop[1],";");
            _CurrentAction = _actions[0];
            if(_actions.size())
                for(std::string s : _actions)
                    _Actions[s] = engine::Action::Actions[s];
        }

        else if(prop[0] != "Name" && prop[0] != "ID" && prop[0] != "ACTION")
            _Properties[prop[0]] = std::stoi(prop[1]);
    }
    
    AssignPosition(_Properties["X"],_Properties["Y"]);
    Render(true);
}

state::Actor::~Actor()
{
}
int state::Actor::Property(std::string prop)
{
    if(prop == "ID") return ID();
    return _Properties[prop];
}
void state::Actor::Property(std::string prop,int value)
{
    _Properties[prop] = value;
    if(prop == "X") AssignPosition(value,_Properties["Y"]);
    if(prop == "Y") AssignPosition(_Properties["X"],value);
    if(prop == "RENDER") value ? Render(true) : Render(false);
}

void state::Actor::OnSelectionAdd()
{
    if(Property("OWNER") != state::WorldHandler::MyID)
        return;
    Selected(true);
    state::Manageable* bg = state::Manager::GetMgrByID(1)->GetByPos(Position());
    bg->Selected(true);
    ChangeAction(_CurrentAction);
}
void state::Actor::OnSelectionRemove()
{
    Selected(false);
    state::Manageable* bg = state::Manager::GetMgrByID(1)->GetByPos(Position());
    bg->Sprite()->setTexture(*bg->Texture()); 
    bg->Selected(false);
    for(state::Manageable* m : state::Manager::GetMgrByName("ACTION_MGR")->Elements())
        m->Render(false);
}

void state::Actor::ChangeAction(std::string new_action)
{
    if(!_Actions[new_action]) return;
    for(state::Manageable* m : state::Manager::GetMgrByName("ACTION_MGR")->Elements())
        m->Render(false);
    std::vector<state::Manageable*> pieces = std::vector<state::Manageable*>();
    for(state::Manageable* m : engine::Action::Actions[new_action]->BasePattern()->Map())
    {
        state::Manageable* _m = new Manageable(m->Name(),"BG_TILE_SELECT");
        _m->AssignPosition(Position().x + m->Position().x, Position().y + m->Position().y);
        _m->Render(true);
        pieces.push_back(_m);
        
    }
            
    _CurrentAction = new_action;
    state::Manager::GetMgrByName("ACTION_MGR")->Elements(pieces);
    engine::SelectionHandler::ChangeAction(new_action);
}


void state::Actor::AssignPosition(int posx,int posy)
{
    Position(sf::Vector2i(posx,posy));
    if(Sprite())
        Sprite()->setPosition(posx*WorldHandler::CurrentWorld->CellSize().x,posy*WorldHandler::CurrentWorld->CellSize().y);
    Position(sf::Vector2i(posx,posy));
    _Properties["X"] = posx;
    _Properties["Y"] = posy;
}
void state::Actor::AssignPosition(sf::Vector2i v0)
{
    AssignPosition(v0.x,v0.y);
}
int state::Actor::GetNetParam(std::string param)
{
    if(param == "ID") return ID();
    if(param == "X") return Position().x;
    if(param == "Y") return Position().y;
    else return _Properties[param];
}

std::string state::Actor::Save()
{
    char id_str[16];
    sprintf(id_str,"%08X",ID());
    std::string output = "Name="+Name() +",ID="+std::string(id_str)+",ACTION=";

    PARSE_MAP(_Actions,std::string,engine::Action*,

    output += it->first +";";

    )
    output[output.length() - 1] = ',';
    PARSE_MAP(_Properties,std::string,int,
    
    output += it->first +"="+std::to_string(it->second)+",";

    )
    output[output.length() - 1] = '\n';
    return output;
}

std::vector<engine::Action*> state::Actor::ActionList()
{
    std::vector<engine::Action*> output;
    PARSE_MAP(_Actions,std::string,engine::Action*,
    output.push_back(it->second);
    )
    return output;
}
std::vector<engine::Action*> state::Actor::PossibleActions()
{
    std::vector<engine::Action*> output;
    for(engine::Action* action : ActionList())
    {
        if(!action->HostileVicinity(this).size() && ((action->OPCode() /1000) == 1))    continue;
        output.push_back(action);
    }
    return output; 
}

engine::Action* state::Actor::ActionOfType(int action_type)
{
    for(engine::Action* a : ActionList())
        if(a->OPCode()/action_type == 1) return a;
    return NULL;
}
