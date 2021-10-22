#include "MainFrame.hpp"
#include "SelectionHandler.hpp"
#include "InputHandler.hpp"
#include <iostream>

MainFrame::MainFrame(std::string name,int h,int w)
{
    Height(h);
    Width(w);
    sf::VideoMode frame_vm(Height(),Width());
    sf::RenderWindow win(frame_vm,name,sf::Style::Default);
    MainFrame::Window = &win;
    OnStart();
    while(MainFrame::Window->isOpen())
    {
        MainFrame::Window->clear(sf::Color::Black);
        Draw();
        if(MainFrame::Window->hasFocus()) 
            Tick();

        MainFrame::Window->display();
    }
            
}


void MainFrame::OnStart()
{
    InputHandler::Initialize();
}
void MainFrame::Draw()
{
    for(int i = 0; i < Manager::Managers.size();i++)
        Manager::GetMgrByID(i)->Draw(MainFrame::Window);
}

void MainFrame::Tick()
{
    
    ON_MOUSE_LEFT(
        //SelectionHandler::Add(BG_TILE(SelectionHandler::GetBGWpos(MousePos).x,SelectionHandler::GetBGWpos(MousePos).y));
        InputHandler::RoutineMouseLeft(MousePos);
    )
    ON_MOUSE_RIGHT(
        InputHandler::RoutineMouseRight(MousePos);
    )

    ON_KEY_DBG(X,
    printf("Close Game !");
    MainFrame::Window->close();
    )
    unsigned char* buffer = InputHandler::RegisterKeyboardInputs();
    if(buffer[sf::Keyboard::M])
    {
        Handler::RoutineTurnBegin();
        Handler::RoutineTurnBeginAsync();
    }
    free(buffer);
    
}