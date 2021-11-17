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
    engine::SelectionHandler::Selection.push_back(m);
}
void engine::SelectionHandler::Remove(state::Manageable** m)
{
    
}

void engine::SelectionHandler::OnMouseLeft(int x,int y)
{
    //std::cout << "CLICK LEFT @ " << x << "::" << y << std::endl;
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    int i = 0;
    items[0] = new state::Manageable();
    items[0]->AssignPosition(x,y);
    for(i = 1; i < state::Manager::Managers.size(); i++)
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
    for(int j = 0; j < state::Manager::Managers.size(); j++)
    {
        if(items[j])
            std::cout << "ITEM" << j << " = " << items[j]->Name() << std::endl;
    }
}
void engine::SelectionHandler::OnMouseRight(int x,int y)
{
    //std::cout << "CLICK RIGHT @ " << x << "::" << y << std::endl;
}