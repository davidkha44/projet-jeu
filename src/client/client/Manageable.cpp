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

void Manageable::OnSelectionAdd()
{
    Sprite()->setTexture(*(FETCH_FROM_MGR("BG_MGR","BG_TILE_SAND")->front()->Texture()));
    Selected(true);
}
void Manageable::OnSelectionRemove()
{
    Sprite()->setTexture(*Texture());
    Selected(false);
}