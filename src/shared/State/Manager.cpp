#include "Manager.h"
#include "Macro.h"

GET_SET(State::Manager,std::string,Name)
GET_SET(State::Manager,char,ID)
GET_SET(State::Manager,std::vector<State::Manageable*>*,Elements)

State::Manager::Manager()
{
    Name("TEST_MGR");
    Elements(new std::vector<State::Manageable*>);
    ID(0);
    Managers.push_back(this);
}

State::Manager::Manager(std::string name,char id)
{
    Name(name);
    ID(id);
    Elements(new std::vector<State::Manageable*>);
    Managers.push_back(this);
}

void State::Manager::Add(State::Manageable* m)
{
    Elements()->push_back(m);
}

void State::Manager::Draw(sf::RenderWindow* rw)
{
    for(State::Manageable* m : *Elements())
    {
        if(m->Render())
            rw->draw(*(m->Sprite()));
    }      
}

State::Manager* State::Manager::GetMgrByName(std::string name)
{
    for(State::Manager* m : Managers)
    {
        if(m->Name() == name)
            return m;
    }
    return NULL;
}
State::Manager* State::Manager::GetMgrByID(int id)
{
    for(State::Manager* m : Managers)
    {
        if(m->ID() == id)
            return m;
    }
    return NULL;
}

std::vector<State::Manageable*>* State::Manager::GetByName(std::string name)
{
    std::vector<State::Manageable*>* output = new std::vector<State::Manageable*>;
    for(State::Manageable* m : *Elements())
    {
        if(m->Name() == name)
            output->push_back(m);
    }
    return output;
}
State::Manageable* State::Manager::GetByID(int id)
{
    for(State::Manageable* m : *Elements())
    {
        if(m->ID() == id)
            return m;
    }
    return NULL;
}
State::Manageable* State::Manager::GetByPos(sf::Vector2i pos)
{
    //POUR PLUS TARD
    return NULL;
}