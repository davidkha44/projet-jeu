#include "SelectionHandler.h"
#include "../shared/state.h"
#include "NetMessageHandler.h"
#include "../../client/render.h"
#include "../shared/state/Manageable.h"
#include <iostream>
#include <sstream>

void engine::SelectionHandler::Add(state::Manageable** m)
{
    if(ProcessSelection(m)) return;
    for(int i = 0; i < Selection.size();i++)
    {
        if(Selection.data()[i][0]->Position().x == m[0]->Position().x && Selection.data()[i][0]->Position().y == m[0]->Position().y )
            return;
    }
    engine::SelectionHandler::Selection.push_back(m);
}
void engine::SelectionHandler::Remove(state::Manageable** m)
{
    int index = 0;
    SelectionState = render::FileHandler::SplitString(SelectionMask[0]," ")[1];
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
int engine::SelectionHandler::ProcessSelection(state::Manageable** m)
{
    std::string _default;
    for(std::string s : SelectionMask)
    {
        std::vector<std::string> items = render::FileHandler::SplitString(s," ");
        if(items[0] == "DEFAULT") _default = items[1];

        if(items[0] == SelectionState && m[state::Manager::GetMgrByName(items[2])->ID()]) 
        {
            FilteredSelection[SelectionState] = (state::Actor*)m[state::Manager::GetMgrByName(items[2])->ID()];
            if(!FilteredSelection[_default]->Selected() || FilteredSelection[_default]->Property("OWNER") != state::WorldHandler::Behaviour->INT("TURN"))
            {
                FilteredSelection[_default] = NULL;
                SelectionState = _default;
                return 1;
            }
            if(SelectionState == _default)
            {
                Packet = engine::Action::Actions[FilteredSelection[_default]->CurrentAction()]->NetCmd()->Format();
                std::cout << Packet.first << "::" << Packet.second << std::endl;
            }
            if(items[1] == "PROCESS")
            {
                std::cout << NetFormat() << std::endl;
                state::WorldHandler::NetCommand(NetFormat());
                SelectionState = _default;
                Trash();
                //FilteredSelection.clear();
                return 1;
            } 
            else SelectionState = items[1];
            std::cout <<"NEXT STATE : " <<SelectionState << std::endl;
            return 0;
        }
    }
}

void engine::SelectionHandler::OnMouseLeft(int x,int y)
{
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    items[0] = new state::Manageable();
    items[0]->Position(sf::Vector2i(x,y));
    for(int i = 1; i < state::Manager::Managers.size(); i++)
    {
        state::Manageable* m = state::Manager::GetMgrByID(i)->GetByPos(x,y);

        if(m && !m->Selected() && m->Render())
        {
            if(SelectionState == render::FileHandler::SplitString(SelectionMask[0]," ")[1]) m->OnSelectionAdd();
            items[i] = m;
        }
        else items[i] = NULL;
    }
    engine::SelectionHandler::Add(items); 
}
void engine::SelectionHandler::OnMouseRight(int x,int y)
{
    
    state::Manageable** items = (state::Manageable**)calloc(state::Manager::Managers.size(), sizeof(state::Manageable*));
    items[0] = new state::Manageable();
    items[0]->Position(sf::Vector2i(x,y));
    engine::SelectionHandler::Remove(items);
    delete items;
}

void engine::SelectionHandler::PrintSelection()
{
    int j = -1;
    for(state::Manageable** m : Selection)
    {
        ++j;
        std::cout << j << ":: { ";
        for(int i = 0; i < state::Manager::Managers.size();i++)
        {
            if(m[i]) std::cout<< state::Manager::GetMgrByID(i)->Name()<<"->" << m[i]->Name() << "; ";
        }
        std::cout << " } " << std::endl;
    }
}

std::string engine::SelectionHandler::NetFormat()
{
    char str[64];
    std::vector<std::string> items = render::FileHandler::SplitString(Packet.second,";");
    int* args = (int*)malloc(items.size()*sizeof(int));
    for(int i = 0; i < items.size();i++)
        args[i] = FilteredSelection[render::FileHandler::SplitString(items[i],".")[0]]->GetNetParam(render::FileHandler::SplitString(items[i],".")[1]);
    return std::string(engine::NetMessageHandler::Fill(Packet.first,args));
}

void engine::SelectionHandler::ChangeAction(std::string new_action)
{
    Packet = engine::Action::Actions[new_action]->NetCmd()->Format();
}