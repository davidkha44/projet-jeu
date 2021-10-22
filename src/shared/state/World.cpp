#include "World.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::World,std::string,Name)
GET_SET(state::World,std::string,ResPath)
GET_SET(state::World,sf::Vector2i,CellSize)
GET_SET(state::World,sf::Vector2i,CellN)

state::World::World()
{
    Name("STD_WORLD");
    ResPath("STD_PATH");
    sf::Vector2i zero(0,0);
    CellSize(zero);
    CellN(zero);
}

state::World::World (std::string name, std::string respath, int csx, int csy, int ncx, int ncy)
{
    Name(name);
    ResPath(respath);
    sf::Vector2i v0(csx,csy);
    sf::Vector2i v1(ncx,ncy);
    CellSize(v0);
    CellN(v1);
}