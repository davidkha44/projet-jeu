#include "World.hpp"
#include <iostream>

//Le programme qui permet de créer le monde

World::World(std::string name,std::string respath,int csx,int csy,int ncx,int ncy)
{
    Name(name);
    ResPath(respath);
    sf::Vector2i v0(csx,csy);
    sf::Vector2i v1(ncx,ncy);
    CellSize(v0);
    CellN(v1);
}
