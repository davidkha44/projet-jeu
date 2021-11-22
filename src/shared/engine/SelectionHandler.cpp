#include "SelectionHandler.h"
#include "../shared/state.h"
#include "../../client/render.h"
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
    ProcessSelection(m);

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
                    _m->OnSelectionRemove();
            }
            delete Selection[i];
            engine::SelectionHandler::Selection.erase(engine::SelectionHandler::Selection.begin() + i);
        }
    }
}

void engine::SelectionHandler::Trash()
{
    for(state::Manageable** m : Selection)
        Remove(m);
    Selection.clear();
}
void engine::SelectionHandler::ProcessSelection(state::Manageable** m)
{
    std::string _default;
    for(std::string s : SelectionMask)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(s," ");
        if(items[0] == "DEFAULT") _default = items[1];
        if(items[0] == SelectionState && m[state::Manager::GetMgrByName(items[2])->ID()]) 
        {
            FilteredSelection[SelectionState] = (state::Actor*)m[state::Manager::GetMgrByName(items[2])->ID()];
            std::cout <<"ADDED : ["<<SelectionState<<"] = " <<FilteredSelection[SelectionState]->Name() << std::endl;
            if(items[1] == "PROCESS")
            {
                std::cout << "ACTION" << std::endl;
                SelectionState = _default;
                FilteredSelection[SelectionState]->OnSelectionRemove();
                Trash();
                //FilteredSelection.clear();
            } 
            else SelectionState = items[1];
            std::cout <<"NEXT STATE : " <<SelectionState << std::endl;
            return;
        }
    }
}

void engine::SelectionHandler::OnMouseLeft(int x,int y)
{
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    items[0] = new state::Manageable();
    sf::Vector2i cpos(x,y);
    items[0]->Position(cpos);
    for(int i = 1; i < state::Manager::Managers.size(); i++)
    {
        state::Manageable* m = state::Manager::GetMgrByID(i)->GetByPos(x,y);
        if(m && !m->Selected() && m->Render())
        {
            m->OnSelectionAdd();
            items[i] = m;
            
        }
    }
    engine::SelectionHandler::Add(items); 
    
}
void engine::SelectionHandler::OnMouseRight(int x,int y)
{
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    items[0] = new state::Manageable();
    items[0]->Position(sf::Vector2i(x,y));
    engine::SelectionHandler::Remove(items);
}