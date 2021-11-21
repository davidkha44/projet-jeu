#include "Actor.h"
#include "Manager.h"
#include <string.h>
#include "../../client/client/Macro.hpp"
#include "../../client/render/FileHandler.h"
#include "../engine.h"
#define COMMA ,

GET_SET(state::Actor, std::map<std::string COMMA int>, Properties)


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
    ID(0xAC000000 + state::Manager::GetMgrByName("ACTOR_MGR")->Elements().size());
    std::vector<std::string> _actions = render::FileHandler::SplitString(args[7],";");
    for(std::string s : _actions)
        _Actions[s] = engine::Action::Actions[s];
}

state::Actor::~Actor()
{
}
int state::Actor::Property(std::string prop)
{
    return _Properties[prop];
}
void state::Actor::Property(std::string prop,int value)
{
    _Properties[prop] = value;
}

void state::Actor::OnSelectionAdd()
{
    Selected(true);
    std::cout << Name() << "::"<< std::hex << ID() << "::OWNER : "<< Property("OWNER") << std::endl;
    
}
void state::Actor::OnSelectionRemove()
{
    Selected(false);
    for(state::Manageable* m : state::Manager::GetMgrByName("ACTION_MGR")->Elements())
        m->Render(false);
}

void state::Actor::ChangeAction(std::string new_action)
{
    for(state::Manageable* m : state::Manager::GetMgrByName("ACTION_MGR")->Elements())
        m->Render(false);
    std::vector<state::Manageable*> pieces = std::vector<state::Manageable*>();
    for(state::Manageable* m : _Actions[new_action]->BasePattern()->Map())
    {
        
        state::Manageable* _m = new Manageable(m->Name(),"BG_TILE_SAND");
        _m->AssignPosition(Position().x + m->Position().x, Position().y + m->Position().y);
        _m->Render(true);
        pieces.push_back(_m);
        
    }
    state::Manager::GetMgrByName("ACTION_MGR")->Elements(pieces);
}

void state::Actor::OnKey(unsigned char* snapshot)
{
    
    if(snapshot[sf::Keyboard::Key::A])
    {
        std::cout << "KEY A" << std::endl;
    }
    if(snapshot[sf::Keyboard::Key::M])
    {
        std::cout << "KEY M" << std::endl;
    }
        
}
