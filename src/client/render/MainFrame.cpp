#include "../../client/client/Macro.hpp"
#include "MainFrame.h"
#include "FileHandler.h"
#include "../shared/state/Manager.h"
#include "../shared/state/WorldHandler.h"
#include "../shared/state/World.h"
#include "../shared/engine/InputHandler.h"
#include "../shared/engine/SelectionHandler.h"
#include "../shared/engine/Script.h"
#include "../shared/state/Actor.h"
#include "../shared/engine/Action.h"
#include "../shared/engine/Pattern.h"
#include <iostream>


GET_SET(render::MainFrame,std::string,Name)
GET_SET(render::MainFrame,int,Height)
GET_SET(render::MainFrame,int,Width)
GET_SET(render::MainFrame,int,Framerate)
GET_SET(render::MainFrame,sf::RenderWindow*,Window)

using namespace std;

render::MainFrame::MainFrame(std::string name, int h, int w)
{
    Name(name);
    Height(h);
    Width(w);
    
}

void render::MainFrame::Draw()
{
    //Demande à chaque Manager de dessiner ses éléments
    for (int i = 0; i < state::Manager::Managers.size(); i++)
    {
       if(state::Manager::GetMgrByID(i)->Elements().size())
            state::Manager::GetMgrByID(i)->Draw(Window());

    }
}
void render::MainFrame::Tick()
{
    //Appelée à chaque frame
    ON_MOUSE_LEFT(
       // std::cout << "MOUSE_LEFT" << std::endl;
        //sf::Vector2i MousePos = sf::Mouse::getPosition(*Window());
        int x = MousePos.x / state::WorldHandler::CurrentWorld->CellSize().x;
        int y = MousePos.y / state::WorldHandler::CurrentWorld->CellSize().y;
        engine::InputHandler::RoutineMouseLeft(x,y);
    )
    ON_MOUSE_RIGHT(
        //std::cout << "MOUSE_RIGHT" << std::endl;
        //sf::Vector2i MousePos = sf::Mouse::getPosition(*Window());
        int x = MousePos.x / state::WorldHandler::CurrentWorld->CellSize().x;
        int y = MousePos.y / state::WorldHandler::CurrentWorld->CellSize().y;
        engine::InputHandler::RoutineMouseRight(x,y);
        /*for(state::World* w : render::FileHandler::DeserializeTable<state::World>("src/client/tables/Worlds.csv","CSV"))
        {
            if(w->Name() == "WORLD_TEST")
                state::WorldHandler::CurrentWorld = w;
                ResizeWindow();
        }*/
    )
    engine::InputHandler::RegisterInputs();
    unsigned char* kb_frame = engine::InputHandler::CompareSnapshots();
    engine::InputHandler::RoutineKey(kb_frame);
    delete kb_frame;

}

void render::MainFrame::Start()
{
    //Lancement de la fenetre + Remplissage des Managers 
    engine::InputHandler::Initialize();
    engine::SelectionHandler::Selection = std::vector<state::Manageable**>();
    InitWorld();
    InitActors();
    sf::VideoMode frame_vm(Height(),Width());
    Window(new sf::RenderWindow(frame_vm, Name(), sf::Style::Default));
    Window()->setFramerateLimit(60);
    while (Window()->isOpen())
    {
        sf::Event event;
         Window()->clear(sf::Color::Black);
        Draw();
        if ( Window()->hasFocus())
            Tick();
        while (Window()->pollEvent(event))
        {
            // Request for closing the window
            if (event.type == sf::Event::Closed)
                Window()->close();
        }
        Window()->display();
    }
}

void render::MainFrame::Resize(int x,int y)
{
    Window()->setSize(sf::Vector2u(x, y));
}

void render::MainFrame::ResizeWindow()
{
    state::World* w = state::WorldHandler::CurrentWorld;
    Window()->setSize(sf::Vector2u(w->CellN().x*w->CellSize().x, w->CellN().y*w->CellSize().y));
}

/*void render::MainFrame::ResizeTexture(std::string path)
{

}*/
void render::MainFrame::InitActors()
{
    //Initialise les acteurs sera rempli plus tard
    render::FileHandler::DeserializeTable<engine::Pattern>("src/client/tables/Patterns.csv","CSV");
    render::FileHandler::DeserializeTable<engine::NetCommand>("src/client/tables/NetMessage.csv","CSV");
    render::FileHandler::DeserializeTable<engine::Action>("src/client/tables/Actions.csv","CSV");
    if(state::WorldHandler::CurrentWorld->Behaviour())
        state::WorldHandler::CurrentWorld->Behaviour()->Run();
    if(state::WorldHandler::Behaviour)
    {
        state::WorldHandler::Behaviour->EVENTS["OnTurnBegin"] = state::WorldHandler::OnTurnBegin;
        state::WorldHandler::Behaviour->EVENTS["OnTurnEnd"] = state::WorldHandler::OnTurnEnd;
        state::WorldHandler::Behaviour->Run();
    }
    //std::vector<state::Actor*> _actors = render::FileHandler::DeserializeTable<state::Actor>("src/client/tables/Actors.csv","CSV");
}

void render::MainFrame::InitWorld()
{
    //Place les Manageables qui composent la map

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


