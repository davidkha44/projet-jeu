#include "SelectionHandler.hpp"
#include <iostream>


void SelectionHandler::Add(Manageable* m)
{
    for(int i = 0; i < Selection.size();i++)
    {
        if(Selection.data()[i] == m)
            return;
    }
    Selection.push_back(m);
    std::cout << "Added " << m->Name() << std::endl; 
    m->OnSelectionAdd();
}

void SelectionHandler::Remove(Manageable* m)
{
    for(int i = 0; i < Selection.size();i++)
    {
        if(Selection.data()[i] == m)
        {
            Selection.erase(Selection.begin() + i);
            m->OnSelectionRemove();
            std::cout << "Removed " << m->Name() << std::endl; 
            return;
        }
    }
}



sf::Vector2i GetBGWpos(sf::Vector2i uv)
{
    sf::Vector2i output(uv.x,uv.y);

    return output;
}