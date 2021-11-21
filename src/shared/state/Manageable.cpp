#include "Manager.h"
#include "../../client/client/Macro.hpp"
#include "engine/SelectionHandler.h"

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
    ResPath(state::Manager::GetMgrByID(0)->GetByName(visual).front()->ResPath());
    Render(true);
    Scale(state::Manager::GetMgrByID(0)->GetByName(visual).front()->Scale());
    Texture(state::Manager::GetMgrByID(0)->GetByName(visual).front()->Texture());
    Sprite(new sf::Sprite());
    Sprite()->setTexture(*(Texture()));
    Sprite()->setScale(state::Manager::GetMgrByID(0)->GetByName(visual).front()->Scale());
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
state::Manageable::Manageable(std::vector<std::string> args)
{
    Name(args[0]);
    ResPath(args[3]);
    ID(std::stoi(args[2]));
    Position(sf::Vector2i(0,0));
    Texture(new sf::Texture());
    Sprite(new sf::Sprite());
    Render(false);
    if(!Texture()->loadFromFile(ResPath()))
        std::cout << "FAIL 2 LOAD" << std::endl;
    Sprite()->setTexture(*Texture());
    Scale(sf::Vector2f(std::stof(args[4]),std::stof(args[5])));
    Sprite()->setScale(Scale().x,Scale().y);
    //state::Manager::GetMgrByName(args[1])->Add(this);
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
    Sprite()->setTexture(*state::Manager::GetMgrByID(0)->GetByID(3)->Texture()); 
}
void state::Manageable::OnSelectionRemove()
{
    Selected(false);
    Sprite()->setTexture(*Texture());
}

void state::Manageable::AssignPosition(int posx,int posy)
{
    Position(sf::Vector2i(posx,posy));
    Sprite()->setPosition(posx*WorldHandler::CurrentWorld->CellSize().x,posy*WorldHandler::CurrentWorld->CellSize().y);
    Position(sf::Vector2i(posx,posy));
}
void state::Manageable::AssignPosition(sf::Vector2i v0)
{
    AssignPosition(v0.x,v0.y);
}


