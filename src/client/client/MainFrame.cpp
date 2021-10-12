#include "MainFrame.hpp"
#include "SelectionHandler.hpp"
#include <iostream>

MainFrame::MainFrame(std::string name,int h,int w)
{
    sf::VideoMode frame_vm(h,w);
    sf::RenderWindow win(frame_vm,name,sf::Style::Default);
    MainFrame::Window = &win;
    Height(h);
    Width(w);
    OnStart();
    while(win.isOpen())
    {
        MainFrame::Window->clear(sf::Color::Blue);
        for(Manager m : Manager::Managers)
            m.Draw(MainFrame::Window); 
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
       
        printf("{ X : %d ; Y : %d }\n",SelectionHandler::GetBGWpos(MousePos).x,SelectionHandler::GetBGWpos(MousePos).y);
    )

    ON_KEY_DBG(X,
    printf("Close Game !");
    MainFrame::Window->close();
    )
    ON_KEY_DBG(M,
    printf("Change Turn !");
    )
}