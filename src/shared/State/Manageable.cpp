#include "Manager.h"
#include "Macro.h"

GET_SET(State::Manageable,std::string,Name)
GET_SET(State::Manageable,std::string,ResPath)
GET_SET(State::Manageable,bool,Render)
GET_SET(State::Manageable,int,ID)
GET_SET(State::Manageable,sf::Texture*,Texture)
GET_SET(State::Manageable,sf::Sprite*,Sprite)
GET_SET(State::Manageable,sf::Vector2i,Position)
GET_SET(State::Manageable,sf::Vector2f,Scale)

State::Manageable::Manageable()
{
    Name("TEST_OBJ");
    ResPath("TEST_RESPATH");
    Render(false);
    ID(0);
    Texture(NULL);
    Sprite(NULL);
    sf::Vector2i vp(0,0);
    sf::Vector2f vs(0,0);
    Position(vp);
    Scale(vs);
}

State::Manageable::Manageable(std::string name,std::string visual)
{
    
    Name(name);
    ID(0xDEAD0000);
    Texture(new sf::Texture());
    Sprite(new sf::Sprite());
    Render(true);
    Texture(State::Manager::GetMgrByName("ASSET_MGR")->GetByName(visual)->front()->Texture());
    Sprite()->setTexture(*Texture());
    Sprite()->setScale(State::Manager::GetMgrByName("ASSET_MGR")->GetByName(visual)->front()->Scale());
}
State::Manageable::Manageable(std::string name,std::string mgr_name,std::string path)
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
    State::Manager::GetMgrByName(mgr_name)->Add(this);
}
State::Manageable::Manageable(std::string name,int id,std::string path)
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

void State::Manageable::OnSelectionAdd()
{
    Selected(true);
}
void State::Manageable::OnSelectionRemove()
{
    Selected(false);
}




