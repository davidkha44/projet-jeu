#ifndef MANAGER_H
#define MANAGER_H
#include "Macro.hpp"
#include "Manageable.hpp"

class Manager
{
    ATTRIBUTE(std::string,Name);
    ATTRIBUTE(int,ID);
    ATTRIBUTE(std::vector<Manageable*>*,Elements);
    STATIC(std::vector<Manager*> Managers);

    public :
    Manager(std::string name);
    
    std::vector<Manageable*>* GetByName(std::string name);
    static Manager* GetMgrByName(std::string name);
    Manageable GetByID(int id);
    void Add(Manageable* element);

    void Remove(Manageable* element);

    void Draw(sf::RenderWindow* rw);

};

#endif