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
    std::cout << "before" << Elements()->size();
    Elements()->push_back(m);
    std::cout << "after" << Elements()->size() << std::endl;
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
        if(!m->Name().compare(name))
            return m;
    }
    return NULL;
}