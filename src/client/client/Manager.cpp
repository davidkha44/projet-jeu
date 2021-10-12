#include "Manager.hpp"
#include <iostream>

Manager::Manager(std::string name)
{
    Name(name);
    ID(0xDEAD0000 + Managers.size());
    Elements(new std::vector<Manageable*>);
    Managers.push_back(*this);
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
        //std::cout << "Draw " << m->Name() << "//" << m->ResPath() << std::endl;
        rw->draw(*(m->Sprite()));
    }
        
}