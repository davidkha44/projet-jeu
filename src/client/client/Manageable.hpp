#ifndef MANAGEABLE_H
#define MANAGEABLE_H
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
    ATTRIBUTE(sf::Texture*,Texture)
    ATTRIBUTE(sf::Sprite*,Sprite)
    ATTRIBUTE(sf::Vector2i,Position)
    ATTRIBUTE(sf::Vector2f,Scale)

    public :
    Manageable(std::string n,std::string visual);
    Manageable(std::string n,std::string mgr_name,std::string respath);
    Manageable(std::string name,int id,std::string path);
    virtual std::string Flush();
    void Tick();
    void Start();
    void OnSelect();
    void OnSelectionAdd();
    void OnSelectionRemove(); 
    void OnSelectAsync();
    void OnSelectionAddAsync();
    void OnSelectionRemoveAsync();
};

#endif