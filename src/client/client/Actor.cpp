#include "Actor.hpp"
#include "WorldHandler.hpp"
#include <stdlib.h> 

Actor::Actor(std::string name,std::string visual,int hp,int dmg,int def,int ap,int mp) : Manageable::Manageable(name,visual)
{
    HP(hp);
    DMG(dmg);
    DEF(def);
    AP(ap);
    MP(mp);

    int rx = rand() % WorldHandler::CurrentWorld()->CellN().x;
    int ry = rand() % WorldHandler::CurrentWorld()->CellN().y;

    Sprite()->setPosition(rx*WorldHandler::CurrentWorld()->CellSize().x,ry*WorldHandler::CurrentWorld()->CellSize().y);
    Position(*(new sf::Vector2i(rx,ry)));
}

Actor::Actor(std::vector<std::string> args) : Manageable::Manageable(args[0],args[1])
{
    HP(std::stoi(args[2]));
    DMG(std::stoi(args[3]));
    DEF(std::stoi(args[4]));
    AP(std::stoi(args[5]));
    MP(std::stoi(args[6]));

    for(std::string s : args)
        PRINTLN(s);
    int rx = rand() % WorldHandler::CurrentWorld()->CellN().x;
    int ry = rand() % WorldHandler::CurrentWorld()->CellN().y;
    //int rx = 10,ry = 10;
    Sprite()->setPosition(rx*WorldHandler::CurrentWorld()->CellSize().x,ry*WorldHandler::CurrentWorld()->CellSize().y);
    Position(*(new sf::Vector2i(rx,ry)));
    PRINTLN("ACTOR DONE")
}
Actor::Actor(std::vector<std::string> args,sf::Vector2i pos) : Manageable::Manageable(args[0],args[1])
{
    HP(std::stoi(args[2]));
    DMG(std::stoi(args[3]));
    DEF(std::stoi(args[4]));
    AP(std::stoi(args[5]));
    MP(std::stoi(args[6]));

    Sprite()->setPosition(pos.x*WorldHandler::CurrentWorld()->CellSize().x,pos.y*WorldHandler::CurrentWorld()->CellSize().y);
    Position(*(new sf::Vector2i(pos.x,pos.y)));
}
std::string Actor::Flush()
{
    return Name()+","+std::to_string(ID())+","+std::to_string(HP())+","+std::to_string(DMG())+","+std::to_string(DEF())
    +","+std::to_string(AP())+","+std::to_string(MP())
    +","+std::to_string(Position().x)+","+std::to_string(Position().y);
}