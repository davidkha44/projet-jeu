
#include "Manager.hpp"
#include <iostream>
#include <fstream>
#include "SelectionHandler.hpp"

Manager::Manager(std::string name)
{
    Name(name);
    Elements(new std::vector<Manageable*>);
    Managers.push_back(this);
}
Manager::Manager(std::string name,int id)
{
    Name(name);
    ID(id);
    Elements(new std::vector<Manageable*>);
    Managers.push_back(this);
}

void Manager::Add(Manageable* m)
{
    Elements()->push_back(m);
    m->ID(m->ID()+(ID() << 16));
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
Manager* Manager::GetMgrByID(int id)
{
    for(Manager* m : Managers)
    {
        if(m->ID() == id)
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
Manageable* Manager::GetByID(int id)
{
    for(Manageable* m : *Elements())
    {
        if(m->ID() == id)
            return m;
    }
    return NULL;
}
Manageable* Manager::GetByPos(sf::Vector2i pos)
{
    for(Manageable* m : *Elements())
    {
        if(SelectionHandler::GetBGWpos(pos).x == m->Position().x && SelectionHandler::GetBGWpos(pos).y == m->Position().y)
            return m;
    }
    return NULL;
}

void Manager::Flush2CSV(int instance,int turn)
{   
    if(!Elements()->size())
        return;
    std::ofstream mfile;
    mfile.open ("/home/ensea/PLT_proper/projet-jeu/src/client/BoardSnapshot/Snapshots/"+Name()+"_"+std::to_string(instance)+"_"+std::to_string(turn)+"_"+".csv");
    for(Manageable* m : *Elements())
    {
        std::cout << m->Flush2CSV() << std::endl;
        mfile << m->Flush2CSV() << std::endl;
    }
        
    mfile.close();
}

bool Manager::PartOf(Manageable* m)
{
    if(GetByID(m->ID()))
        return true;
    return false;
}