#include "World.h"
#include "Macro.h"

GET_SET(State::World,std::string,Name)
GET_SET(State::World,std::string,ResPath)
GET_SET(State::World,sf::Vector2i,CellSize)
GET_SET(State::World,sf::Vector2i,CellN)

State::World::World()
{
    Name("STD_WORLD");
    ResPath("STD_PATH");
    sf::Vector2i zero(0,0);
    CellSize(zero);
    CellN(zero);
}

State::World::World (std::string name, std::string respath, int csx, int csy, int ncx, int ncy)
{
    Name(name);
    ResPath(respath);
    sf::Vector2i v0(csx,csy);
    sf::Vector2i v1(ncx,ncy);
    CellSize(v0);
    CellN(v1);
}