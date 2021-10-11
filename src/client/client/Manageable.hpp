#ifndef MYHEADEFILE_H
#define MYHEADEFILE_H
#include "Macro.hpp"
#include <SFML/Graphics.hpp>

class Manageable
{
    ATTRIBUTE(std::string,Name)
    ATTRIBUTE(std::string,ResPath)
    ATTRIBUTE(int,ID)
    ATTRIBUTE(bool,Update)
    ATTRIBUTE(bool,Render)
    ATTRIBUTE(bool,Selected)
    ATTRIBUTE(bool,Collider)
    ATTRIBUTE(bool,Async)
    ATTRIBUTE(sf::Texture,Texture)
    ATTRIBUTE(sf::Sprite,Sprite)
    ATTRIBUTE(sf::Vector2f,Position)

    public :
    Manageable(std::string n,std::string respath);
    void Tick();
    void Start();
    void OnSelect();
    void OnSelectionAdd();
    void OnSelectionRemove(); 
    void OnSelectAsync();
    void OnSelectionAddAsync();
    void OnSelectionRemoveAsync();
    void Load();
};

#endif