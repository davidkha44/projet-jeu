#include "../../client/client/Macro.hpp"
#include "MainFrame.h"
#include "FileHandler.h"
#include "../shared/state/Manager.h"
#include "../shared/state/Actor.h"


GET_SET(render::MainFrame,std::string,Name)
GET_SET(render::MainFrame,int,Height)
GET_SET(render::MainFrame,int,Width)
GET_SET(render::MainFrame,int,Framerate)

render::MainFrame::MainFrame(std::string name, int h, int w)
{
    Name(name);
    Height(h);
    Width(w);
}

void render::MainFrame::Draw()
{
    for (int i = 0; i < state::Manager::Managers.size(); i++)
    {
       if(state::Manager::GetMgrByID(i)->Elements().size())
       {
            //std::cout << state::Manager::GetMgrByID(i)->Name() << "::" <<(int)state::Manager::GetMgrByID(i)->ID() << "::" << state::Manager::GetMgrByID(i)->Elements().size()<< std::endl;
            state::Manager::GetMgrByID(i)->Draw(MainFrame::Window);
       }

    }
}
void render::MainFrame::Tick()
{

}

void render::MainFrame::Start()
{
    InitWorld();
    InitActors();
    sf::VideoMode frame_vm(Width(),Height());
    MainFrame::Window = new sf::RenderWindow(frame_vm, Name(), sf::Style::Default);
    while (MainFrame::Window->isOpen())
    {
        sf::Event event;
        MainFrame::Window->clear(sf::Color::Black);
        Draw();
        if (MainFrame::Window->hasFocus())
            Tick();
        while (Window->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                Window->close();
        }
        MainFrame::Window->display();
    }
}

void render::MainFrame::InitActors()
{
    std::vector<state::Actor*> _actors = render::FileHandler::DeserializeTable<state::Actor>("src/client/tables/Actors.csv","CSV");
}

void render::MainFrame::InitWorld()
{
    state::World* w = state::WorldHandler::CurrentWorld;
    std::ifstream file(w->ResPath());
    std::cout << "W DIM : " << w->CellN().x <<"::"<< w->CellN().y << std::endl;
    state::Manager* mgr = state::Manager::GetMgrByID(0);
    int lines = 0,col = 0;
    for( std::string line; getline( file, line ); )
    {
        if(line.find('#') == std::string::npos)
        {
            std::vector<std::string> strs = render::FileHandler::SplitString(line,",");
            for(int i = 0; i < w->CellN().x;i++)
            {
                state::Manageable* ref = mgr->GetByID(std::stoi(strs[i]));
                state::Manageable* item = new state::Manageable("TILE_"+std::to_string(col)+"_"+std::to_string(lines),ref->Name());
                item->ID(0xFF000000 + ((col & 0xFF) << 8) + (lines & 0xFF));
                item->AssignPosition(col,lines);
                state::Manager::GetMgrByID(1)->Add(item);
                col++;
            } 
        }
        col = 0;
        lines++;
        if(lines == w->CellSize().y)
            return;
    }
}