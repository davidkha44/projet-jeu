#include "Manager.h"
#include "Manageable.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::Manager,std::string,Name)
GET_SET(state::Manager,char,ID)
GET_SET(state::Manager,int,Flush)
GET_SET(state::Manager,std::vector<state::Manageable*>,Elements)

state::Manager::Manager()
{
    Name("TEST_MGR");
    Elements(std::vector<state::Manageable*>());
    ID(0);
    Managers.push_back(this);
}

state::Manager::~Manager()
{

}

state::Manager::Manager(std::string name,char id)
{
    Name(name);
    ID(id);
    Elements( std::vector<state::Manageable*>());
    Managers.push_back(this);
}
state::Manager::Manager(std::vector<std::string> args)
{
    Name(args[0]);
    ID((char)(std::stoi(args[1])& 0xFF));
    Elements(std::vector<state::Manageable*>());
    Flush(std::stoi(args[2]));
    Managers.push_back(this);
}
void state::Manager::Add(state::Manageable* m)
{
    std::vector<state::Manageable*>* v = &_Elements;
    v->push_back(m);
}
void state::Manager::Remove(state::Manageable* m)
{
    std::vector<state::Manageable*>* v = &_Elements;
    int i = 0;
    for(state::Manageable* _m : _Elements)
    {
        if(m == _m)
            _Elements.erase(_Elements.begin() + i);
        i++;
    }
}

void state::Manager::Draw(sf::RenderWindow* rw)
{
    for(state::Manageable* m : Elements())
    {
        if(m->Render())
            rw->draw(*(m->Sprite()));
        else
        {
            switch(Flush())
            {
                case 1 :
                {
                    state::Manageable* _m = m;
                    m->Selected(false);
                    Remove(m);
                }
                break;
                case 2 :
                {
                    state::Manageable* _m = m;
                    Remove(m);
                    m->Selected(false);
                    delete _m;
                }
                break;
            }
        }
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
    for(state::Manager* m : state::Manager::Managers)
    {
        if(m->ID() == (char)(id & 0xFF))
            return m;
    }
    return NULL;
}

std::vector<state::Manageable*> state::Manager::GetByName(std::string name)
{
    std::vector<state::Manageable*> output = std::vector<state::Manageable*>();
    for(state::Manageable* m : Elements())
    {
        if(m->Name() == name)
            output.push_back(m);
    }
    return output;
}
state::Manageable* state::Manager::GetByID(int id)
{
    for(state::Manageable* m : Elements())
    {
        if(m->ID() == id)
            return m;
    }
    return NULL;
}

state::Manageable* state::Manager::GetByPos(int x,int y)
{
    for(state::Manageable* m : Elements())
    {
        if(m->Position().x == x && m->Position().y == y)
         return m;   
    }
    return NULL;
}

state::Manageable* state::Manager::GetByPos(sf::Vector2i v0)
{
    return GetByPos(v0.x,v0.y);
}
