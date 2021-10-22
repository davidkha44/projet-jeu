#include "Manager.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::Manager,std::string,Name)
GET_SET(state::Manager,char,ID)
GET_SET(state::Manager,std::vector<state::Manageable*>*,Elements)

state::Manager::Manager()
{
    Name("TEST_MGR");
    Elements(new std::vector<state::Manageable*>);
    ID(0);
    Managers.push_back(this);
}

state::Manager::Manager(std::string name,char id)
{
    Name(name);
    ID(id);
    Elements(new std::vector<state::Manageable*>);
    Managers.push_back(this);
}

void state::Manager::Add(state::Manageable* m)
{
    Elements()->push_back(m);
}

void state::Manager::Draw(sf::RenderWindow* rw)
{
    for(state::Manageable* m : *Elements())
    {
        if(m->Render())
            rw->draw(*(m->Sprite()));
    }      
}

state::Manager* state::Manager::GetMgrByName(std::string name)
{
    for(state::Manager* m : Managers)
    {
        if(m->Name() == name)
            return m;
    }
    return NULL;
}
state::Manager* state::Manager::GetMgrByID(int id)
{
    for(state::Manager* m : Managers)
    {
        if(m->ID() == id)
            return m;
    }
    return NULL;
}

std::vector<state::Manageable*>* state::Manager::GetByName(std::string name)
{
    std::vector<state::Manageable*>* output = new std::vector<state::Manageable*>;
    for(state::Manageable* m : *Elements())
    {
        if(m->Name() == name)
            output->push_back(m);
    }
    return output;
}
state::Manageable* state::Manager::GetByID(int id)
{
    for(state::Manageable* m : *Elements())
    {
        if(m->ID() == id)
            return m;
    }
    return NULL;
}
state::Manageable* state::Manager::GetByPos(sf::Vector2i pos)
{
    //POUR PLUS TARD
    return NULL;
}