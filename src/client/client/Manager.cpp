#include "Manager.hpp"
#include <iostream>

Manager::Manager(std::string name)
{
    Name(name);
    ID(0xDEAD0000 + Managers.size());
    Elements(new std::vector<Manageable*>);
    Managers.push_back(this);
}

void Manager::Add(Manageable* m)
{
    Elements()->push_back(m);
}

void Manager::Draw(sf::RenderWindow* rw)
{
    for(Manageable* m : *Elements())
    {
        if(m->Render())
            rw->draw(*(m->Sprite()));
    }      
}

Manager* Manager::GetMgrByName(std::string name)
{
    for(Manager* m : Managers)
    {
        if(m->Name() == name)
            return m;
    }
    return NULL;
}

std::vector<Manageable*>* Manager::GetByName(std::string name)
{
    std::vector<Manageable*>* output = new std::vector<Manageable*>;
    for(Manageable* m : *Elements())
    {
        if(m->Name() == name)
            output->push_back(m);
    }
    return output;
}