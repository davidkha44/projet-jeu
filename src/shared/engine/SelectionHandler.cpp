#include "SelectionHandler.h"
#include "../shared/state/Manager.h"
#include "../shared/state/Manageable.h"
#include <iostream>

void engine::SelectionHandler::Add(state::Manageable** m)
{
    for(int i = 0; i < Selection.size();i++)
    {
        if(Selection.data()[i][0]->Position().x == m[0]->Position().x && Selection.data()[i][0]->Position().y == m[0]->Position().y )
            return;
    }
    for(int i = 1; i < state::Manager::Managers.size();i++)
    {
        if(m[i] && m[i]->Render())
            std::cout << "Added " << m[i]->Name() << std::endl;
    }
    engine::SelectionHandler::Selection.push_back(m);
}
void engine::SelectionHandler::Remove(state::Manageable** m)
{
    int index = 0;
    for(int i = 0; i < Selection.size();i++)
    {
        if(Selection.data()[i][0]->Position().x == m[0]->Position().x && Selection.data()[i][0]->Position().y == m[0]->Position().y )
        {
            for(int j = 1; j < state::Manager::Managers.size();j++)
            {
                state::Manageable* _m = Selection.data()[i][j];
                if(_m && _m->Render() && _m->Selected())
                {
                    std::cout << "Removed " << _m->Name() << std::endl;
                    _m->OnSelectionRemove();
                    
                }
            }
            delete Selection[i];
            engine::SelectionHandler::Selection.erase(engine::SelectionHandler::Selection.begin() + i);
        }
    }
}

void engine::SelectionHandler::OnMouseLeft(int x,int y)
{
    //std::cout << "CLICK LEFT a@ " << x << "::" << y << std::endl;
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    items[0] = new state::Manageable();
    sf::Vector2i cpos(x,y);
    items[0]->Position(cpos);
    for(int i = 1; i < state::Manager::Managers.size(); i++)
    {
        state::Manageable* m = state::Manager::GetMgrByID(i)->GetByPos(x,y);
        if(m)
        {
            if(!m->Selected() && m->Render())
            {
                m->OnSelectionAdd();
                items[i] = m;
            }
        }
    }
    engine::SelectionHandler::Add(items);
    // for(int j = 0; j < state::Manager::Managers.size(); j++)
    // {
    //     if(items[j])
    //         std::cout << "ITEM" << j << " = " << items[j]->Name() << std::endl;
    // }
}
void engine::SelectionHandler::OnMouseRight(int x,int y)
{
    //std::cout << "CLICK RIGHT @ " << x << "::" << y << std::endl;
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    items[0] = new state::Manageable();
    sf::Vector2i cpos(x,y);
    items[0]->Position(cpos);
    engine::SelectionHandler::Remove(items);
}