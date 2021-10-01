#include "MainFrame.hpp"

MainFrame::MainFrame(std::string name,int h,int w)
{
    sf::Vector2f frame_vs(h,w);
    sf::VideoMode frame_vm(frame_vs.x,frame_vs.y);
    sf::RenderWindow win(frame_vm,name,sf::Style::Default);
    Window(&win);
    Height(h);
    Width(w);
    OnStart();
    while(win.isOpen())
    {
        Tick();
        Window()->clear(sf::Color::Blue);
        Window()->display();
    }
            
}

void MainFrame::OnStart()
{

}

void MainFrame::Tick()
{
        
    ON_KEY_DBG(X,
    printf("Close Game !");
    Window()->close();
    )
    ON_KEY_DBG(M,
    printf("Change Turn !");
    )
}