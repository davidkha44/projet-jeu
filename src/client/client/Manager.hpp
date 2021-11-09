#ifndef MANAGER_H
#define MANAGER_H
#include "Macro.hpp"
#include "Manageable.hpp"

class Manager
{
    ATTRIBUTE(std::string,Name);
    ATTRIBUTE(int,ID);
    ATTRIBUTE(bool,Flush);
    ATTRIBUTE(std::vector<Manageable*>*,Elements);
    STATIC(std::vector<Manager*> Managers);

    public :
    Manager(std::string name);
    Manager(std::string name,int id);
    
    std::vector<Manageable*>* GetByName(std::string name);
    static Manager* GetMgrByName(std::string name);
    static Manager* GetMgrByID(int id);
    Manageable* GetByID(int id);
    Manageable* GetByPos(sf::Vector2i pos);
    void Flush2CSV(int instance,int turn);
    void LoadFromCSV(int instance,int turn);
    void Add(Manageable* element);
    bool PartOf(Manageable* m);

    void Remove(Manageable* element);

    void Draw(sf::RenderWindow* rw);

};

#endif