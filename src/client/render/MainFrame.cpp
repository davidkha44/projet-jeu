#include "../../client/client/Macro.hpp"
#include "MainFrame.h"
#include "FileHandler.h"
#include "../shared/state/Manager.h"


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
    sf::VideoMode frame_vm(Height(), Width());
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

void render::MainFrame::InitWorld()
{
    state::World* w = state::WorldHandler::CurrentWorld;
    std::ifstream file(w->ResPath());
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
                std::cout << ref->ResPath() << std::endl;
                state::Manageable* item = new state::Manageable("TILE_"+std::to_string(col)+"_"+std::to_string(lines),ref->Name());
                std::cout << item->Name() << std::endl;
                item->ID(0xFF000000 + ((col & 0xFF) << 8) + (lines & 0xFF));
                item->AssignPosition(col,lines);
                //std::cout << item->Sprite()->getPosition().x << "::" << item->Sprite()->getPosition().y << std::endl;
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