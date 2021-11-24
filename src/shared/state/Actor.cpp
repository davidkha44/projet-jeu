#include "Actor.h"
#include "Manager.h"
#include <string.h>
#include "../../client/client/Macro.hpp"
#include "../../client/render/FileHandler.h"
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
    _CurrentAction = "STD_MOVE";
    ID(0xAC000000 + state::Manager::GetMgrByName("ACTOR_MGR")->Elements().size());
    std::vector<std::string> _actions = render::FileHandler::SplitString(args[7],";");
    if(_actions.size())
    {
        for(std::string s : _actions)
            _Actions[s] = engine::Action::Actions[s];
    }

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
}

void state::Actor::OnSelectionAdd()
{
    Selected(true);
    state::Manageable* bg = state::Manager::GetMgrByID(1)->GetByPos(Position());
    //bg->Sprite()->setTexture(*state::Manager::GetMgrByID(0)->GetByID(3)->Texture()); 
    bg->Selected(true);
    ChangeAction("STD_MOVE");
    std::cout << Name() << "::"<< std::hex << ID() << "::OWNER : "<< Property("OWNER") << std::endl;  
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
    for(state::Manageable* m : state::Manager::GetMgrByName("ACTION_MGR")->Elements())
        m->Render(false);
    std::vector<state::Manageable*> pieces = std::vector<state::Manageable*>();
        std::cout << "ICI" << std::endl;
    for(state::Manageable* m : engine::Action::Actions[new_action]->BasePattern()->Map())
    {
        
        state::Manageable* _m = new Manageable(m->Name(),"BG_TILE_SAND");
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
    Sprite()->setPosition(posx*WorldHandler::CurrentWorld->CellSize().x,posy*WorldHandler::CurrentWorld->CellSize().y);
    Position(sf::Vector2i(posx,posy));
    _Properties["X"] = posx;
    _Properties["Y"] = posy;
    _Properties["COORD"] = ((posx & 0xFFFF) << 16) + (posy & 0xFFFF);
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
