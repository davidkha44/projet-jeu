#include "../../client/client/Macro.hpp"
#include "MainFrame.h"
#include "../shared/state.h"
#include "../shared/engine.h"
#include "../shared/ai.h"
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
render::MainFrame::~MainFrame(){
    
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
        int x = MousePos.x / state::WorldHandler::CurrentWorld->CellSize().x;
        int y = MousePos.y / state::WorldHandler::CurrentWorld->CellSize().y;
        engine::InputHandler::RoutineMouseLeft(x,y);
    )
    ON_MOUSE_RIGHT(
        int x = MousePos.x / state::WorldHandler::CurrentWorld->CellSize().x;
        int y = MousePos.y / state::WorldHandler::CurrentWorld->CellSize().y;
        engine::InputHandler::RoutineMouseRight(x,y);
    )
    engine::InputHandler::RegisterInputs();
    unsigned char* kb_frame = engine::InputHandler::CompareSnapshots();
    if(kb_frame[sf::Keyboard::G])
        state::WorldHandler::OnTurnBegin();
    engine::InputHandler::RoutineKey(kb_frame);
    delete kb_frame;

}

void render::MainFrame::WakeUp()
{
    engine::InputHandler::Initialize();
    PRINTLN("WU IH OK");
    state::WorldHandler::Initialize();
    PRINTLN("WU WH OK");

    engine::SelectionHandler::Selection = std::vector<state::Manageable**>();
    PRINTLN("WU SH OK");

    InitWorld();
    PRINTLN("WU IW OK");

    InitActors();
    PRINTLN("WU IA OK");

}

void render::MainFrame::Start()
{
    //Lancement de la fenetre + Remplissage des Managers 
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

render::MainFrame* render::MainFrame::FromLaunchArgs (std::string path)
{
    //Charge et parcours le fichiers de configuration LaunchArgs.csv
    engine::FileHandler::DeserializeTable<engine::Script>("res/tables/Scripts.csv","CSV");
    engine::Script::STATIC_FUNCTIONS["CheckPosition"] = state::Manager::CheckPosition;
    engine::Script::STATIC_FUNCTIONS["Destroy"] = state::Manager::Destroy;
    engine::Script::STATIC_FUNCTIONS["EndTurn"] = state::Player::EndTurn;
    engine::Script::STATIC_FUNCTIONS["RandomInt"] = ai::RandomAI::RandomInt;
    engine::Script::STATIC_FUNCTIONS["MoveToward"] = ai::Heuristics::MoveToward;
    engine::Script::STATIC_FUNCTIONS["IsInReach"] = engine::Action::IsInReach;
    engine::Script::STATIC_FUNCTIONS["Exist"] = state::WorldHandler::Exist;
    state::WorldHandler::Initialize();
    PARSE_CSV_LINES(path,'#',
    if(items[0] == "SCENE")
    {
        for(state::World* w : engine::FileHandler::DeserializeTable<state::World>("res/tables/Worlds.csv","CSV"))
        {
            PRINTLN(w->Name());
            if(w->Name() == items[1])
                state::WorldHandler::CurrentWorld = w;
        }
    }
    if(items[0] == "GRID_THICKNESS")
        state::WorldHandler::CurrentWorld->ApplyGridThickness(std::stoi(items[1]));
    if(items[0] == "RULES")
        state::WorldHandler::Behaviour = engine::Script::Scripts[items[1]];
    if(items[0] == "FLUSH_PATH")
        state::WorldHandler::BSPath = items[1];

    )
    return new render::MainFrame("PLT",state::WorldHandler::CurrentWorld->CellN().x*state::WorldHandler::CurrentWorld->CellSize().x,
    state::WorldHandler::CurrentWorld->CellN().y*state::WorldHandler::CurrentWorld->CellSize().y);
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
    engine::FileHandler::DeserializeTable<engine::Pattern>("res/tables/Patterns.csv","CSV");
    engine::FileHandler::DeserializeTable<engine::NetCommand>("res/tables/NetMessage.csv","CSV");
    engine::FileHandler::DeserializeTable<engine::Action>("res/tables/Actions.csv","CSV");
    if(state::WorldHandler::CurrentWorld->Behaviour())
        state::WorldHandler::CurrentWorld->Behaviour()->Run();
    if(state::WorldHandler::Behaviour)
    {
        state::WorldHandler::Behaviour->EVENTS["OnTurnBegin"] = state::WorldHandler::OnTurnBegin;
        state::WorldHandler::Behaviour->EVENTS["OnTurnEnd"] = state::WorldHandler::OnTurnEnd;
        state::WorldHandler::Behaviour->Run();
        for(state::Player* p : state::WorldHandler::Players)
            if(p->Behaviour())
                p->Behaviour()->RunFunction("InitializePlayer",(int*)NULL);
    }
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
            std::vector<std::string> strs = engine::FileHandler::SplitString(line,",");
            for(int i = 0; i < w->CellN().x;i++)
            {
                state::Manageable* ref = mgr->GetByID(std::stoi(strs[i]));
                state::Manageable* item = new state::Manageable("TILE_"+std::to_string(col)+"_"+std::to_string(lines),ref->Name());
                item->ID(0xFF000000 + ((std::stoi(strs[i]) & 0xFF) << 16) +((col & 0xFF) << 8) + (lines & 0xFF));
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


