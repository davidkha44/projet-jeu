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
state::World::~World()
{

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

state::World::World (std::vector<std::string> args)
{
    Name(args[0]);
    ResPath(args[1]);
    sf::Vector2i v0(std::stoi(args[2]),std::stoi(args[3]));
    sf::Vector2i v1(std::stoi(args[4]),std::stoi(args[5]));
    CellSize(v0);
    CellN(v1);
}
