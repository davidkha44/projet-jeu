#include "Manageable.hpp"
#include "Manager.hpp"
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
    Render(false);
    Sprite()->setTexture(*Texture());
}

void Manageable::Load()
{
    Texture()->loadFromFile(ResPath());
}

void Manageable::OnSelectionAdd()
{
    Sprite()->setTexture(*(FETCH_FROM_MGR("BG_MGR","BG_TILE_SAND")->front()->Texture()));
}
void Manageable::OnSelectionRemove()
{
    Sprite()->setTexture(*Texture());
}