#include "Manager.h"
#include "../../client/client/Macro.hpp"

GET_SET(state::Manageable,std::string,Name)
GET_SET(state::Manageable,std::string,ResPath)
GET_SET(state::Manageable,bool,Render)
GET_SET(state::Manageable,bool,Selected)
GET_SET(state::Manageable,int,ID)
GET_SET(state::Manageable,sf::Texture*,Texture)
GET_SET(state::Manageable,sf::Sprite*,Sprite)
GET_SET(state::Manageable,sf::Vector2i,Position)
GET_SET(state::Manageable,sf::Vector2f,Scale)

state::Manageable::Manageable()
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
state::Manageable::~Manageable()
{

}

state::Manageable::Manageable(std::string name,std::string visual)
{
    
    Name(name);
    ID(0xDEAD0000);
    Texture(new sf::Texture());
    Sprite(new sf::Sprite());
    Render(true);
    Texture(state::Manager::GetMgrByName("ASSET_MGR")->GetByName(visual)->front()->Texture());
    Sprite()->setTexture(*Texture());
    Sprite()->setScale(state::Manager::GetMgrByName("ASSET_MGR")->GetByName(visual)->front()->Scale());
}
state::Manageable::Manageable(std::string name,std::string mgr_name,std::string path)
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
    state::Manager::GetMgrByName(mgr_name)->Add(this);
}
state::Manageable::Manageable(std::string name,int id,std::string path)
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

void state::Manageable::OnSelectionAdd()
{
    Selected(true);
}
void state::Manageable::OnSelectionRemove()
{
    Selected(false);
}

void state::Manageable::AssignPosition(int posx,int posy)
{
    sf::Vector2i v0(posx,posy);
    Position(v0);
}
void state::Manageable::AssignPosition(sf::Vector2i v0)
{
    Position(v0);
}


