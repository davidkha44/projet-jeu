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
    std::cout << "Added " << m->Name() <<"::"<< std::hex <<m->ID() << std::endl; 
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
            std::cout << "Removed " << m->Name() <<"::"<< std::hex << m->ID() << std::endl; 
            return;
        }
    }
}

void SelectionHandler::OnTurnBeginAsync()
{
    //Flush();
    std::cout << "ON_TURN_BEGIN_ASYNC_SH" << std::endl;
}
void SelectionHandler::OnTurnBegin()
{
    //Flush();
    std::cout << "ON_TURN_BEGIN_SH" << std::endl;
}

sf::Vector2i SelectionHandler::GetBGWpos(sf::Vector2i uv)
{
    sf::Vector2i output(uv.x/WorldHandler::CurrentWorld->CellSize().x,uv.y/WorldHandler::CurrentWorld->CellSize().y);
    return output;
}

void SelectionHandler::OnMouseLeft(sf::Vector2i MousePos)
{
    for(Manager* m : Manager::Managers)
    {
        Manageable* item = m->GetByPos(MousePos);
        if(item)
        {
            if(item->Render())
                Add(item);
        }
            
    }
}
void SelectionHandler::OnMouseRight(sf::Vector2i MousePos)
{
    for(Manager* m : Manager::Managers)
    {
        Manageable* item = m->GetByPos(MousePos);
        if(item)
        {
            if(item->Render())
                Remove(item);
        }
    }
}