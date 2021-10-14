#include "MainFrame.hpp"
#include "SelectionHandler.hpp"
#include "Manager.hpp"
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
        for(Manager* m : Manager::Managers)
            m->Draw(MainFrame::Window); 
        if(MainFrame::Window->hasFocus()) 
            Tick();

        MainFrame::Window->display();
    }
            
}

void DrawBGWorld(Manager* bgmgr)
{
   
        
}

void MainFrame::OnStart()
{
    

}

void MainFrame::Tick()
{
    
    ON_MOUSE_LEFT(
        SelectionHandler::Add(BG_TILE(SelectionHandler::GetBGWpos(MousePos).x,SelectionHandler::GetBGWpos(MousePos).y));
    )
    ON_MOUSE_RIGHT(
        SelectionHandler::Remove(BG_TILE(SelectionHandler::GetBGWpos(MousePos).x,SelectionHandler::GetBGWpos(MousePos).y));
    )

    ON_KEY_DBG(X,
    printf("Close Game !");
    MainFrame::Window->close();
    )
    ON_KEY_DBG(M,
    printf("Change Turn !");
    )
}