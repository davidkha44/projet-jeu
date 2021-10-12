#include "Manageable.hpp"
#include <thread>

Manageable::Manageable(std::string name,std::string path)
{
    
    Name(name);
    ID(0xDEAD0000);
    ResPath(path);
    if(path.empty())
        return;
    Texture(new sf::Texture());
    Sprite(new sf::Sprite());
    Texture()->loadFromFile(path);
    //std::thread asth(&Manageable::Load,this);
    Sprite()->setTexture(*Texture());
}

void Manageable::Load()
{
    Texture()->loadFromFile(ResPath());
}