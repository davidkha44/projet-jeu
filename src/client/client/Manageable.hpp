#include "Macro.hpp"
#include <SFML/Graphics.hpp>

class Manageable
{
    ATTRIBUTE(std::string,Name);
    ATTRIBUTE(std::string,ResPath);
    ATTRIBUTE(int,ID);
    ATTRIBUTE(bool,Update);
    ATTRIBUTE(bool,Render);
    ATTRIBUTE(bool,Selected);
    ATTRIBUTE(bool,Collider);
    ATTRIBUTE(bool,Async);
    ATTRIBUTE(bool,Async);
    ATTRIBUTE(sf::Texture,Texture);
    ATTRIBUTE(sf::Sprite,Sprite);
    ATTRIBUTE(sf::Vector2f,Position);

    public :
    virtual void Tick();
    virtual void Start();
    virtual void OnSelect();
    virtual void OnSelectionAdd();
    virtual void OnSelectionRemove(); 
    virtual void OnSelectAsync();
    virtual void OnSelectionAddAsync();
    virtual void OnSelectionRemoveAsync();


};