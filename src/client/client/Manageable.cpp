#include "Manager.hpp"
#include "WorldHandler.hpp"
#include <thread>

Manageable::Manageable(std::string name,std::string visual)
{
    
    Name(name);
    ID(0xDEAD0000);
    Texture(new sf::Texture());
    Sprite(new sf::Sprite());
    Render(true);
    Texture(FETCH_FROM_MGR("ASSET_MGR",visual)->front()->Texture());
    Sprite()->setTexture(*Texture());
    Sprite()->setScale(FETCH_FROM_MGR("ASSET_MGR",visual)->front()->Scale());
}
Manageable::Manageable(std::string name,std::string mgr_name,std::string path)
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
    Manager::GetMgrByName(mgr_name)->Add(this);
}
Manageable::Manageable(std::string name,int id,std::string path)
{
    
    Name(name);
    ID(id);
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
    Sprite()->setTexture(*(FETCH_FROM_MGR("ASSET_MGR","BG_TILE_SAND")->front()->Texture()));
    Selected(true);
}
void Manageable::OnSelectionRemove()
{
    Sprite()->setTexture(*Texture());
    Selected(false);
}

std::string Manageable::Flush2CSV()
{
    return Name()+","+std::to_string(ID())+","+std::to_string(Position().x)+","+std::to_string(Position().y);
}

void Manageable::AssignPosition(sf::Vector2i pos)
{
    AssignPosition(pos.x,pos.y);
}
void Manageable::AssignPosition(int px,int py)
{
    Sprite()->setPosition(px*WorldHandler::CurrentWorld()->CellSize().x,py*WorldHandler::CurrentWorld()->CellSize().y);
    Position(*(new sf::Vector2i(px,py)));
}
